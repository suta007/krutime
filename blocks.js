Blockly.Blocks["KruTime.read"] = {
    init: function() {
      this.appendDummyInput()
          .appendField(Blockly.Msg.KruTime_READ);
      this.setInputsInline(true);
      this.setOutput(true, "Number");
      this.setColour(0);
   this.setTooltip("");
   this.setHelpUrl("");
    }
};