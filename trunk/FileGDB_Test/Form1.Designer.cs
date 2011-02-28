namespace FileGDB_Test
{
    partial class Form1
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
            this.btnCreateFGDB = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.txtFgdbPath = new System.Windows.Forms.TextBox();
            this.btnOpenClose = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.btnCreateTable = new System.Windows.Forms.Button();
            this.btnGetDatasetTypes = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnCreateFGDB
            // 
            this.btnCreateFGDB.Location = new System.Drawing.Point(12, 32);
            this.btnCreateFGDB.Name = "btnCreateFGDB";
            this.btnCreateFGDB.Size = new System.Drawing.Size(143, 63);
            this.btnCreateFGDB.TabIndex = 0;
            this.btnCreateFGDB.Text = "Create FGDB";
            this.btnCreateFGDB.UseVisualStyleBackColor = true;
            this.btnCreateFGDB.Click += new System.EventHandler(this.btnCreateFGDB_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "FGDB Path";
            // 
            // txtFgdbPath
            // 
            this.txtFgdbPath.Location = new System.Drawing.Point(80, 6);
            this.txtFgdbPath.Name = "txtFgdbPath";
            this.txtFgdbPath.Size = new System.Drawing.Size(326, 20);
            this.txtFgdbPath.TabIndex = 2;
            this.txtFgdbPath.Text = "C:\\Projects\\fgdb_dotnet\\code\\db\\test.gdb";
            // 
            // btnOpenClose
            // 
            this.btnOpenClose.Location = new System.Drawing.Point(161, 32);
            this.btnOpenClose.Name = "btnOpenClose";
            this.btnOpenClose.Size = new System.Drawing.Size(143, 63);
            this.btnOpenClose.TabIndex = 3;
            this.btnOpenClose.Text = "Open/Close FGDB";
            this.btnOpenClose.UseVisualStyleBackColor = true;
            this.btnOpenClose.Click += new System.EventHandler(this.btnOpenClose_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.Location = new System.Drawing.Point(310, 32);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(143, 63);
            this.btnDelete.TabIndex = 4;
            this.btnDelete.Text = "Delete FGDB";
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // btnCreateTable
            // 
            this.btnCreateTable.Location = new System.Drawing.Point(12, 101);
            this.btnCreateTable.Name = "btnCreateTable";
            this.btnCreateTable.Size = new System.Drawing.Size(143, 63);
            this.btnCreateTable.TabIndex = 5;
            this.btnCreateTable.Text = "Create Table";
            this.btnCreateTable.UseVisualStyleBackColor = true;
            this.btnCreateTable.Click += new System.EventHandler(this.btnCreateTable_Click);
            // 
            // btnGetDatasetTypes
            // 
            this.btnGetDatasetTypes.Location = new System.Drawing.Point(161, 101);
            this.btnGetDatasetTypes.Name = "btnGetDatasetTypes";
            this.btnGetDatasetTypes.Size = new System.Drawing.Size(143, 63);
            this.btnGetDatasetTypes.TabIndex = 6;
            this.btnGetDatasetTypes.Text = "Get Dataset Types";
            this.btnGetDatasetTypes.UseVisualStyleBackColor = true;
            this.btnGetDatasetTypes.Click += new System.EventHandler(this.btnGetDatasetTypes_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(477, 299);
            this.Controls.Add(this.btnGetDatasetTypes);
            this.Controls.Add(this.btnCreateTable);
            this.Controls.Add(this.btnDelete);
            this.Controls.Add(this.btnOpenClose);
            this.Controls.Add(this.txtFgdbPath);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnCreateFGDB);
            this.Name = "Form1";
            this.Text = "C:\\Projects\\fgdb_dotnet\\code\\db\\TestDB.gdb";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCreateFGDB;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtFgdbPath;
        private System.Windows.Forms.Button btnOpenClose;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.Button btnCreateTable;
        private System.Windows.Forms.Button btnGetDatasetTypes;
    }
}

