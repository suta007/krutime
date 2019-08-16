/*
Blockly.JavaScript["KruTime.read"] = function(block) {
    var code = 'DEV_I2C1.KRUTIME(0, 0x0F).getRawValue()';
    return [code, Blockly.JavaScript.ORDER_NONE];
  };
*/
/*
  Blockly.JavaScript['KruTime.start'] = function(block) {
    var value_gatenum = Blockly.JavaScript.valueToCode(block, 'GateNum', Blockly.JavaScript.ORDER_ATOMIC);
    var code = 'DEV_I2C1.KRUTIME(0, 0x0F).StartTime('+value_gatenum+');';
    return code;
  };
*/
Blockly.JavaScript["KruTime.start2"] = function(block) {
  var value_gatenum2 = Blockly.JavaScript.valueToCode(
    block,
    "GateNum",
    Blockly.JavaScript.ORDER_ATOMIC
  );
  var code = "DEV_I2C1.KRUTIME(0, 0x0F).StartTime2(" + value_gatenum2 + ")";
  return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript["KruTime.setgate"] = function(block) {
  var value_gate = Blockly.JavaScript.valueToCode(
    block,
    "Gate",
    Blockly.JavaScript.ORDER_ATOMIC
  );
  var code = "DEV_I2C1.KRUTIME(0, 0x0F).SetGatePin(" + value_gate + ");";
  return code;
};

Blockly.JavaScript["KruTime.readgate"] = function(block) {
  var code = "DEV_I2C1.KRUTIME(0, 0x0F).getGateTime()";
  return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript["KruTime.stop"] = function(block) {
  var code = "DEV_I2C1.KRUTIME(0, 0x0F).StopTime();";
  return code;
};

Blockly.JavaScript["KruTime.clear"] = function(block) {
  var code = "DEV_I2C1.KRUTIME(0, 0x0F).ClearTime();";
  return code;
};
