var filename = "~/klatch.kvtml";

var action = new Object;

action.text = "Append to " + filename;

action.run = function() {
  print(results.length);
  for (var i = 0; i < results.length; i++) {
    print(results[i].word);
    print(results[i].text);
  }
}
