//Remove All Empty Columns in the Entire Workbook
function removeEmptyColumns() {
var ss = SpreadsheetApp.getActive();
var allsheets = ss.getSheets();
for (var s in allsheets){
var sheet=allsheets[s]
var maxColumns = sheet.getMaxColumns(); 
var lastColumn = sheet.getLastColumn();
if (maxColumns-lastColumn != 0){
      sheet.deleteColumns(lastColumn+1, maxColumns-lastColumn);
      }
  }
}

//Remove All Empty Rows in the Entire Workbook
function removeEmptyRows() {
var ss = SpreadsheetApp.getActive();
var allsheets = ss.getSheets();
for (var s in allsheets){
var sheet=allsheets[s]
var maxRows = sheet.getMaxRows(); 
var lastRow = sheet.getLastRow();
if (maxRows-lastRow != 0){
      sheet.deleteRows(lastRow+1, maxRows-lastRow);
      }
  }
}