# Autosar Layered Architecture

![Autosar Layered architecture](http://autonom.com.tr/wp-content/uploads/2020/03/Autosar-Layered-Software-Architecture.jpg)

## Microcontroller

this is the microcontroller as a hardware resource such as peripherals and external specs of the microcontroller

## Microcontroller Abstraction Layer (Mcal)

The Microcontroller Abstraction Layer is the
lowest software layer of the Basic Software.
It contains **internal drivers**, which are software
modules with direct access to the µC and
internal peripherals

this module is HW dependent and is usually supplied by mC supplier

## ECU Abstraction Layer

The ECU Abstraction Layer interfaces the
drivers of the Microcontroller Abstraction
Layer. It also contains drivers for external
devices.
It offers an API for access to peripherals and
devices regardless of their location (µC
internal/external) and their connection to the
µC (port pins, type of interface)

abstract upper layers from ECU layout

contains external drivers for peripherals that are on the ECU level such as external EEPROM

## Complex Drivers Layer

The Complex Drivers Layer spans from the
hardware to the RTE.

- Provide the possibility to integrate special purpose
functionality, e.g. drivers for devices:
which are not specified within AUTOSAR,
with very high timing constrains or
for migration purposes etc.

- **Implementation**: might be application, µC and ECU
hardware dependent
**Upper Interface**: might be application, µC and ECU hardware dependent

## Services Layer

The Services Layer is the highest layer of the Basic
Software which also applies for its relevance for
the application software: while access to I/O
signals is covered by the ECU Abstraction Layer,
the Services Layer offers:

- Operating system functionality
- Vehicle network communication and management
services
- Memory services (NVRAM management)
- Diagnostic Services (including UDS communication, error
memory and fault treatment)
- ECU state management, mode management
- Logical and temporal program flow monitoring (Wdg
manager)

## RTE

The RTE is a layer providing communication services(methods)
to the application software (AUTOSAR Software
Components and/or AUTOSAR Sensor/Actuator
components).
Above the RTE the software architecture style
changes from “layered“ to “component style“.
The AUTOSAR Software Components communicate
with other components (inter and/or intra ECU)
and/or services via the RTE.

such as Making AUTOSAR Software Components independent
from the mapping to a specific ECU.

**Implementation**: ECU and application specific
(generated individually for each ECU)
Upper Interface: completely ECU independent

**Virtual Function Bus** help communicaion between SWCs even if it is not within the same ECU

## Libraries

Libraries are a collection of functions for
related purposes:

- can be called by BSW modules (that
including the RTE), SW-Cs, libraries
or integration code
- run in the context of the caller in the
same protection environment
- can only call libraries
- are re-entrant
- do not have internal states
- do not require any initialization
- are synchronous, i.e. they do not have
wait points

**The following libraries are specified within AUTOSAR:**

- Fixed point mathematical,
- Floating point mathematical,
- Interpolation for fixed point data,
- Interpolation for floating point data,
- Bit handling,
- E2E communication,
- CRC calculation,
- Extended functions (e.g. 64bits calculation, filtering, etc.)

### Some Remarks

The AUTOSAR Basic Software supports the following configuration classes:

1. **Pre-compile time**
   - Preprocessor instructions
   - Code generation (selection or synthetization)
2. **Link time**
   - Constant data outside the module; the data can be configured after the module has been
compiled
3. **Post-build time**
   - Loadable constant data outside the module. Very similar to [2], but the data is located in a specific memory segment that allows reloading (e.g. reflashing in ECU production line)

**Use cases**
**Pre-compile** time configuration would be chosen for

- Enabling/disabling optional functionality
This allows to exclude parts of the source code that are not needed

- Optimization of performance and code size
Using #defines results in most cases in more efficient code than
access to constants or even access to constants via pointers.
Generated code avoids code and runtime overhead.
