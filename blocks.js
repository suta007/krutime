/*
Blockly.Blocks["KruTime.read"] = {
    init: function() {
      this.appendDummyInput()
          .appendField(Blockly.Msg.KruTime_Title)
          .appendField(Blockly.Msg.KruTime_Read);
      this.setInputsInline(true);
      this.setOutput(true, "Number");
      this.setColour(0);
   this.setTooltip("");
   this.setHelpUrl(Blockly.Msg.KruTime_URL);
    }
};
*/

/*
Blockly.Blocks['KruTime.start'] = {
    init: function() {
        this.appendValueInput("GateNum")
            .setCheck("Number")
            .appendField(Blockly.Msg.KruTime_Title)
            .appendField(Blockly.Msg.KruTime_Start)
            .appendField(Blockly.Msg.KruTime_GateNum);
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(0);
    this.setTooltip("");
    this.setHelpUrl(Blockly.Msg.KruTime_URL);
    }
  };
*/

Blockly.Blocks["KruTime.start2"] = {
  init: function() {
    this.appendValueInput("GateNum")
      .setCheck("Number")
      .appendField(Blockly.Msg.KruTime_Title)
      .appendField(Blockly.Msg.KruTime_Start)
      .appendField(Blockly.Msg.KruTime_GateNum);
    this.setInputsInline(true);
    this.setOutput(true, "Boolean");
    this.setColour(0);
    this.setTooltip("");
    this.setHelpUrl(Blockly.Msg.KruTime_URL);
  }
};

Blockly.Blocks["KruTime.setgate"] = {
  init: function() {
    this.appendValueInput("Gate")
      .setCheck("Number")
      .appendField(Blockly.Msg.KruTime_Title)
      .appendField(Blockly.Msg.KruTime_ReadTime)
      .appendField(Blockly.Msg.KruTime_Gate);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(0);
    this.setTooltip("");
    this.setHelpUrl(Blockly.Msg.KruTime_URL);
  }
};

Blockly.Blocks["KruTime.readgate"] = {
  init: function() {
    this.appendDummyInput()
      .appendField(Blockly.Msg.KruTime_Title)
      .appendField(Blockly.Msg.KruTime_ReadGate);
    this.setInputsInline(true);
    this.setOutput(true, "Number");
    this.setColour(0);
    this.setTooltip("");
    this.setHelpUrl(Blockly.Msg.KruTime_URL);
  }
};

Blockly.Blocks["KruTime.stop"] = {
  init: function() {
    this.appendDummyInput()
      .appendField(Blockly.Msg.KruTime_Title)
      .appendField(Blockly.Msg.KruTime_Stop);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(0);
    this.setTooltip("");
    this.setHelpUrl(Blockly.Msg.KruTime_URL);
  }
};

Blockly.Blocks["KruTime.clear"] = {
  init: function() {
    this.appendDummyInput()
      .appendField(Blockly.Msg.KruTime_Title)
      .appendField(Blockly.Msg.KruTime_Clear);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(0);
    this.setTooltip("");
    this.setHelpUrl(Blockly.Msg.KruTime_URL);
  }
};
