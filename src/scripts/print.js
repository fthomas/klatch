// This is a very simple script that should demonstrate the basics of
// writing scripts for Klatch.

var action = new Object;

action.text = "Print Selected Results";

action.run = function() {
  print("Selected results: " + results.length + "\n");

  for (var i = 0; i < results.length; ++i) {
    var res = results[i];
    print("Word: " + res.word);
    print("Database: " + res.database + ", " + res.databaseDescription);
    print("Text: " + res.text);
  }
}
