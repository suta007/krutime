Blockly.JavaScript["KruTime.read"] = function(block) {
    // TODO: Assemble JavaScript into code variable.
    var code = 'DEV_I2C1.KRUTIME(0, 0x8).getRawValue()';
    // TODO: Change ORDER_NONE to the correct strength.
    return [code, Blockly.JavaScript.ORDER_NONE];
  };