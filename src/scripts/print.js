// This is a very simple script that should demonstrate the basics of
// writing scripts for Klatch.

// To be available as action in the context menu of the main list view,
// the scripts need to have the "action" or "actions" properties, where
// "actions" can be an array of different actions.
var action = new Object;

// This is the text that is displayed inside Klatch for this action.
action.text = "Print Selected Results";

// This function is executed whenever this action is triggered.
action.run = function() {
  // The selected definitions in the main list view are available in
  // the global scope as the "results" array.
  print("Selected results: " + results.length + "\n");

  for (var i = 0; i < results.length; ++i) {
    var res = results[i];

    // Each object in this array has the properties "word", "database",
    // "databaseDescription", and "text".
    print("Word: " + res.word);
    print("Database: " + res.database + ", " + res.databaseDescription);
    print("Text: " + res.text);
  }
}
