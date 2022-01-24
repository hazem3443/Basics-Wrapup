# CAN-Bus (Control Area Network)

The CAN bus was developed by BOSCH (1) as a multi-master, message broadcast system that specifies a
maximum signaling rate of 1 megabit per second (bps). Unlike a traditional network such as USB or
Ethernet, CAN does not send large blocks of data point-to-point from node A to node B under the
supervision of a central bus master. In a CAN network, many short messages like temperature or RPM
are broadcast to the entire network, which provides for data consistency in every node of the system.