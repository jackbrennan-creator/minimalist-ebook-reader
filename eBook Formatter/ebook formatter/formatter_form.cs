using System;
using System.IO;
using System.Windows.Forms;

namespace ebook_cleaner
{
  public partial class formatter_form : Form
  {
    private string path     = "";
    private string contents = "";
    
    public formatter_form()
    {
      InitializeComponent();
      CenterToScreen();
    }

    private void open_button_Click(object sender, EventArgs e)
    {
      OpenFileDialog dialog = new OpenFileDialog();
      dialog.Title  = "Open ebook File";
      dialog.Filter = "Text Files|*.txt;*.text|All Files|*.*";
      if (dialog.ShowDialog(this) == DialogResult.OK)
      {
        path = dialog.FileName;
        StreamReader file = new StreamReader(dialog.FileName);
        contents = file.ReadToEnd();
        file.Close();
        display.Clear();
        display.AppendText(contents);
      }
    }

    private void process_button_Click(object sender, EventArgs e)
    {
      contents = contents.Replace("\r\n", "\n");
      contents = contents.Replace("\n\n", "$$$");
      contents = contents.Replace("\n", " ");
      contents = contents.Replace("$$$", "\n");
      if (replace_quotes.Checked)
      {
        contents = contents.Replace("“", "\"");
        contents = contents.Replace("”", "\"");
        contents = contents.Replace("‘", "'");
        contents = contents.Replace("'", "'");
      }
      if (replace_apostrophies.Checked) contents = contents.Replace("’", "'");
      if (remove_underscores.Checked)   contents = contents.Replace("_", " ");
      display.Clear();
      display.AppendText(contents);
    }

    private void save_button_Click(object sender, EventArgs e)
    {
      SaveFileDialog dialog = new SaveFileDialog();
      dialog.Title    = "Save ebook File As";
      dialog.Filter   = "Text Files|*.txt;*.text|All Files|*.*";
      dialog.FileName = Path.GetFileName(path);
      if (dialog.ShowDialog(this) == DialogResult.OK)
      {
        StreamWriter file = new StreamWriter(dialog.FileName);
        file.Write(contents);
        file.Close();
      }
    }
  }
}
