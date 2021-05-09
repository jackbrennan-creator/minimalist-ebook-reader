namespace ebook_cleaner
{
  partial class formatter_form
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.open_button = new System.Windows.Forms.Button();
      this.process_button = new System.Windows.Forms.Button();
      this.save_button = new System.Windows.Forms.Button();
      this.display = new System.Windows.Forms.TextBox();
      this.replace_quotes = new System.Windows.Forms.CheckBox();
      this.replace_apostrophies = new System.Windows.Forms.CheckBox();
      this.remove_underscores = new System.Windows.Forms.CheckBox();
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.SuspendLayout();
      // 
      // open_button
      // 
      this.open_button.BackColor = System.Drawing.Color.SteelBlue;
      this.open_button.ForeColor = System.Drawing.Color.White;
      this.open_button.Location = new System.Drawing.Point(12, 12);
      this.open_button.Name = "open_button";
      this.open_button.Size = new System.Drawing.Size(68, 28);
      this.open_button.TabIndex = 0;
      this.open_button.Text = "Open";
      this.open_button.UseVisualStyleBackColor = false;
      this.open_button.Click += new System.EventHandler(this.open_button_Click);
      // 
      // process_button
      // 
      this.process_button.BackColor = System.Drawing.Color.SteelBlue;
      this.process_button.ForeColor = System.Drawing.Color.White;
      this.process_button.Location = new System.Drawing.Point(12, 46);
      this.process_button.Name = "process_button";
      this.process_button.Size = new System.Drawing.Size(68, 28);
      this.process_button.TabIndex = 1;
      this.process_button.Text = "Process";
      this.process_button.UseVisualStyleBackColor = false;
      this.process_button.Click += new System.EventHandler(this.process_button_Click);
      // 
      // save_button
      // 
      this.save_button.BackColor = System.Drawing.Color.SteelBlue;
      this.save_button.ForeColor = System.Drawing.Color.White;
      this.save_button.Location = new System.Drawing.Point(12, 80);
      this.save_button.Name = "save_button";
      this.save_button.Size = new System.Drawing.Size(68, 28);
      this.save_button.TabIndex = 2;
      this.save_button.Text = "Save";
      this.save_button.UseVisualStyleBackColor = false;
      this.save_button.Click += new System.EventHandler(this.save_button_Click);
      // 
      // display
      // 
      this.display.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                  | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.display.Location = new System.Drawing.Point(191, 12);
      this.display.Multiline = true;
      this.display.Name = "display";
      this.display.ScrollBars = System.Windows.Forms.ScrollBars.Both;
      this.display.Size = new System.Drawing.Size(498, 651);
      this.display.TabIndex = 3;
      this.display.WordWrap = false;
      // 
      // replace_quotes
      // 
      this.replace_quotes.AutoSize = true;
      this.replace_quotes.Location = new System.Drawing.Point(12, 296);
      this.replace_quotes.Name = "replace_quotes";
      this.replace_quotes.Size = new System.Drawing.Size(146, 17);
      this.replace_quotes.TabIndex = 4;
      this.replace_quotes.Text = "Replace Unicode Quotes";
      this.replace_quotes.UseVisualStyleBackColor = true;
      // 
      // replace_apostrophies
      // 
      this.replace_apostrophies.AutoSize = true;
      this.replace_apostrophies.Location = new System.Drawing.Point(12, 319);
      this.replace_apostrophies.Name = "replace_apostrophies";
      this.replace_apostrophies.Size = new System.Drawing.Size(173, 17);
      this.replace_apostrophies.TabIndex = 5;
      this.replace_apostrophies.Text = "Replace Unicode Apostrophies";
      this.replace_apostrophies.UseVisualStyleBackColor = true;
      // 
      // remove_underscores
      // 
      this.remove_underscores.AutoSize = true;
      this.remove_underscores.Location = new System.Drawing.Point(12, 342);
      this.remove_underscores.Name = "remove_underscores";
      this.remove_underscores.Size = new System.Drawing.Size(129, 17);
      this.remove_underscores.TabIndex = 6;
      this.remove_underscores.Text = "Remove Underscores";
      this.remove_underscores.UseVisualStyleBackColor = true;
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label1.Location = new System.Drawing.Point(12, 270);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(126, 13);
      this.label1.TabIndex = 7;
      this.label1.Text = "Additional Formatting";
      // 
      // label2
      // 
      this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label2.Location = new System.Drawing.Point(12, 144);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(161, 83);
      this.label2.TabIndex = 8;
      this.label2.Text = "Formats a text file as a sequence of paragraphs separated by single newline chara" +
          "cters.\r\n";
      // 
      // formatter_form
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.LightSteelBlue;
      this.ClientSize = new System.Drawing.Size(701, 675);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.remove_underscores);
      this.Controls.Add(this.replace_apostrophies);
      this.Controls.Add(this.replace_quotes);
      this.Controls.Add(this.display);
      this.Controls.Add(this.save_button);
      this.Controls.Add(this.process_button);
      this.Controls.Add(this.open_button);
      this.Name = "formatter_form";
      this.Text = "eBook Formatter";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button open_button;
    private System.Windows.Forms.Button process_button;
    private System.Windows.Forms.Button save_button;
    private System.Windows.Forms.TextBox display;
    private System.Windows.Forms.CheckBox replace_quotes;
    private System.Windows.Forms.CheckBox replace_apostrophies;
    private System.Windows.Forms.CheckBox remove_underscores;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
  }
}

