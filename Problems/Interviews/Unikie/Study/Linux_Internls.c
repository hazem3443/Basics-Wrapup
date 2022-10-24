// Uses the Linux I2C API to send and receive data from a Jrk G2.
// NOTE: The Jrk's input mode must be "Serial / I2C / USB".
// NOTE: For reliable operation on a Raspberry Pi, enable the i2c-gpio
//   overlay and use the I2C device it provides (usually /dev/i2c-3).
// NOTE: You might need to change the 'const char * device' line below
//   to specify the correct I2C device.
// NOTE: You might need to change the `const uint8_t address' line below
// to match the device number of your Jrk.
 
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
 
// Opens the specified I2C device.  Returns a non-negative file descriptor
// on success, or -1 on failure.
int open_i2c_device(const char * device)
{
  int fd = open(device, O_RDWR);
  if (fd == -1)
  {
    perror(device);
    return -1;
  }
  return fd;
}
 
// Sets the target, returning 0 on success and -1 on failure.
//
// For more information about what this command does, see the "Set Target"
// command in the "Command reference" section of the Jrk G2 user's guide.
int jrk_set_target(int fd, uint8_t address, uint16_t target)
{
  uint8_t command[] = {
    (uint8_t)(0xC0 + (target & 0x1F)),
    (uint8_t)((target >> 5) & 0x7F),
  };
  struct i2c_msg message = { address, 0, sizeof(command), command };
  struct i2c_rdwr_ioctl_data ioctl_data = { &message, 1 };
  int result = ioctl(fd, I2C_RDWR, &ioctl_data);
  if (result != 1)
  {
    perror("failed to set target");
    return -1;
  }
  return 0;
}
 
// Gets one or more variables from the Jrk (without clearing them).
// Returns 0 for success, -1 for failure.
int jrk_get_variable(int fd, uint8_t address, uint8_t offset,
  uint8_t * buffer, uint8_t length)
{
  uint8_t command[] = { 0xE5, offset };
  struct i2c_msg messages[] = {
    { address, 0, sizeof(command), command },
    { address, I2C_M_RD, length, buffer },
  };
  struct i2c_rdwr_ioctl_data ioctl_data = { messages, 2 };
  int result = ioctl(fd, I2C_RDWR, &ioctl_data);
  if (result != 2)
  {
    perror("failed to get variables");
    return -1;
  }
  return 0;
}
 
// Gets the Target variable from the jrk or returns -1 on failure.
int jrk_get_target(int fd, uint8_t address)
{
  uint8_t buffer[2];
  int result = jrk_get_variable(fd, address, 0x02, buffer, sizeof(buffer));
  if (result) { return -1; }
  return buffer[0] + 256 * buffer[1];
}
 
// Gets the Feedback variable from the jrk or returns -1 on failure.
int jrk_get_feedback(int fd, uint8_t address)
{
  // 0x04 is the offset of the feedback variable in the "Variable reference"
  // section of the Jrk user's guide.  The variable is two bytes long.
  uint8_t buffer[2];
  int result = jrk_get_variable(fd, address, 0x04, buffer, sizeof(buffer));
  if (result) { return -1; }
  return buffer[0] + 256 * buffer[1];
}
 
int main()
{
  // Choose the I2C device.
  const char * device = "/dev/i2c-2";
 
  // Set the I2C address of the Jrk (the device number).
  const uint8_t address = 11;
 
  int fd = open_i2c_device(device);
  if (fd < 0) { return 1; }
 
  int feedback = jrk_get_feedback(fd, address);
  if (feedback < 0) { return 1; }
  printf("Feedback is %d.\n", feedback);
 
  int target = jrk_get_target(fd, address);
  if (target < 0) { return 1; }
  printf("Target is %d.\n", target);
 
  int new_target = (target < 2048) ? 2248 : 1848;
  printf("Setting target to %d.\n", new_target);
  int result = jrk_set_target(fd, address, new_target);
  if (result) { return 1; }
 
  close(fd);
  return 0;
}