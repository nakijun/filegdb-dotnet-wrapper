using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using FileGDB_DotNet;

namespace FileGDB_Test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnCreateFGDB_Click(object sender, EventArgs e)
        {
            GeodatabaseNet fgdb = new GeodatabaseNet();
            fgdb.CreateGeodatabase(txtFgdbPath.Text);

            // Close the DB after creating it
            fgdb.CloseGeodatabase();

            MessageBox.Show("Create FGDB completed");
        }

        private void btnOpenClose_Click(object sender, EventArgs e)
        {
            GeodatabaseNet fgdb = new GeodatabaseNet();
            fgdb.OpenGeodatabase(txtFgdbPath.Text);

            // Close the DB after creating it
            fgdb.CloseGeodatabase();

            MessageBox.Show("Open/Close FGDB Called, result: ");
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            GeodatabaseNet fgdb = new GeodatabaseNet();
            fgdb.DeleteGeodatabase(txtFgdbPath.Text);

            MessageBox.Show("Delete FGDB Called, result: ");
        }

        private void btnCreateTable_Click(object sender, EventArgs e)
        {
            GeodatabaseNet fgdb = new GeodatabaseNet();
            // try to delete the fgdb first
            fgdb.DeleteGeodatabase(txtFgdbPath.Text);
            
            // Create the fgdb
            fgdb.CreateGeodatabase(txtFgdbPath.Text);

            string streetsTableDef = "";
            using (StreamReader sw = new StreamReader("Table Schema\\Streets.xml"))
            {
                streetsTableDef = sw.ReadToEnd();
            }

            TableNet table = fgdb.CreateTable(streetsTableDef, "");

            MessageBox.Show("Created table, result: ");
        }

        private void btnGetDatasetTypes_Click(object sender, EventArgs e)
        {
            GeodatabaseNet fgdb = new GeodatabaseNet();
            // try to delete the fgdb first
            fgdb.DeleteGeodatabase(txtFgdbPath.Text);
            
            // Create the fgdb
            fgdb.CreateGeodatabase(txtFgdbPath.Text);
            
            string streetsTableDef = "";
            using (StreamReader sw = new StreamReader("Table Schema\\Streets.xml"))
            {
                streetsTableDef = sw.ReadToEnd();
            }

            TableNet table = fgdb.CreateTable(streetsTableDef, "");

            fgdb.OpenGeodatabase(txtFgdbPath.Text);
            List<String> datasetTypes = fgdb.GetDatasetTypes();

            MessageBox.Show("Dataset types fetched.");
        }
    }
}
