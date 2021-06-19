function doGet(e) {
  let humidity = '';
  let temperature = '';

  try {
    temperature = e.parameters.temperature;
    humidity = e.parameters.humidity;

    saveValues(temperature, humidity);

    return ContentService.createTextOutput('Saved temperature = ' + temperature + ' and humidity = ' + humidity);
  } catch {
    Logger.log(err);
  }
}

function saveValues(temperature, humidity) {
  try {
    let date = new Date();
    let spreadsheet = SpreadsheetApp.openByUrl('Link to your spreadsheet');
    let sheet = spreadsheet.getSheetByName('Logs');
    let row = sheet.getLastRow() + 1;
    sheet.getRange('A' + row).setValue(date.getDate() + '/' + date.getMonth() + '/' + date.getFullYear());
    sheet.getRange('B' + row).setValue(date.getHours() + ':' + date.getMinutes() + ':' + date.getSeconds());
    sheet.getRange('C' + row).setValue(temperature);
    sheet.getRange('D' + row).setValue(humidity);
  } catch {
    Logger.log(err);
  }
}
