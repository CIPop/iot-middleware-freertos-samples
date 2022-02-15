# Azure Data Explorer Table

```
.create table WatsonIoT ( 
    EnqueuedTime:datetime, 
    Device:string, 
    R0:long,
    R1:long,
    R2:long,
    R3:long,
    R4:long,
    R5:long,
    R6:long,
    R7:long,
    R8:long,
    R9:long,
    R10:long,
    R11:long,
    R12:long,
    LR:long,
    PC:long,
    XPSR:long,
    CFSR:long,
    HFSR:long,
    DFSR:long,
    MMFAR:long,
    BFAR:long,
    AFSR:long
    );
```

```
.alter table WatsonIoT policy streamingingestion enable;
```

# IoT Cen

## Custom Filtering

```
import "iotc" as iotc;
{
    Device: .device.id,
    EnqueuedTime: .enqueuedTime,
    R0: .telemetry | iotc::find(.name == "R0").value,
    R1: .telemetry | iotc::find(.name == "R1").value,
    R2: .telemetry | iotc::find(.name == "R2").value,
    R3: .telemetry | iotc::find(.name == "R3").value,
    R4: .telemetry | iotc::find(.name == "R4").value,
    R5: .telemetry | iotc::find(.name == "R5").value,
    R6: .telemetry | iotc::find(.name == "R6").value,
    R7: .telemetry | iotc::find(.name == "R7").value,
    R8: .telemetry | iotc::find(.name == "R8").value,
    R9: .telemetry | iotc::find(.name == "R9").value,
    R10: .telemetry | iotc::find(.name == "R10").value,
    R11: .telemetry | iotc::find(.name == "R11").value,
    R12: .telemetry | iotc::find(.name == "R12").value,
    LR: .telemetry | iotc::find(.name == "LR").value,
    PC: .telemetry | iotc::find(.name == "PC").value,
    XPSR: .telemetry | iotc::find(.name == "XPSR").value,
    CFSR: .telemetry | iotc::find(.name == "CFSR").value,
    HFSR: .telemetry | iotc::find(.name == "HFSR").value,
    DFSR: .telemetry | iotc::find(.name == "DFSR").value,
    MMFAR: .telemetry | iotc::find(.name == "MMFAR").value,
    BFAR: .telemetry | iotc::find(.name == "BFAR").value,
    AFSR: .telemetry | iotc::find(.name == "AFSR").value
}
```

## Default

```
# The transformation query specified here will be used to change each exported 
# message into a different format. You can get started using the example below,
# and learn more about the language in documentation:
# https://aka.ms/dataexporttransformation
{
    schema: "default@v1",
    applicationId: .applicationId,
    deviceId: .device.id,
    templateId: .device.templateId,
    messageSource: .messageSource,
    enqueuedTime: .enqueuedTime,
    telemetry: .telemetry | map({ key: .name, value: .value }) | from_entries,
    messageProperties: .messageProperties,
    enrichments: .enrichments,
    component: .component,
    module: .module
}
```


# Kusto Query

```
WatsonIoT |
project 
    CrashTime=EnqueuedTime,
    Device,
    tohex(CFSR, 8), 
    InstructionAccessViolation=(binary_and(CFSR, binary_shift_left(1, 0))!=0),
    MemoryManagerUnstackingError=(binary_and(CFSR, binary_shift_left(1, 3))!=0),
    InstructionBusError=(binary_and(CFSR, binary_shift_left(1, 8))!=0),
    MMFARValid=(binary_and(CFSR, binary_shift_left(1, 7))!=0),
    tohex(MMFAR, 8),
    BFARValid=(binary_and(CFSR, binary_shift_left(1, 15))!=0),
    tohex(BFAR, 8),
    PreciseError=(binary_and(CFSR, binary_shift_left(1, 9))!=0),
    tohex(LR, 8),  
    tohex(PC, 8)
```
