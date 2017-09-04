function getAllVibrationData() {
  var firebaseUrl = "https://vibrationtracker.firebaseio.com/";
  var secret = "HNDdIwPV1RuY3qhm2P7APiiwg4VDCAWQViRj2dIB"
  var base = FirebaseApp.getDatabaseByUrl(firebaseUrl, secret);
  var data = base.getData();
  for(var i in data) {
    Logger.log(data[i]);
  }
}

//Vibration Data Sheet ID: 1yRw4ugaMgVAFgK0d8IgTsVrXXr6Cg-314PHw8RrvSJ4

function writeSheets() {
  var ss = SpreadsheetApp.openById("1yRw4ugaMgVAFgK0d8IgTsVrXXr6Cg-314PHw8RrvSJ4");
  var sheet = ss.getSheets()[0];
  var firebaseUrl = "https://vibrationtracker.firebaseio.com/";
  var secret = "HNDdIwPV1RuY3qhm2P7APiiwg4VDCAWQViRj2dIB";  // get this from firebase project settings
  var base = FirebaseApp.getDatabaseByUrl(firebaseUrl, secret);
  var data = base.getData();
  var keys = Object.keys(data["vibration-data"]);
  var sheetRow = [];
  var entryKeys;
  for (index in keys) {
    sheetRow = [];
    entryKeys = Object.keys(data["vibration-data"][keys[index]])
    for (i in entryKeys) {
      sheetRow.push(data["vibration-data"][keys[index]][entryKeys[i]]);
    }
  }
      sheet.appendRow(sheetRow);                           
}
