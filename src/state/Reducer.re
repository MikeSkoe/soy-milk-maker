type globalAction =
   | GoGame
   | GoMenu;

let dispatch = _state => fun
   | GoGame => State.Game(State.makeGameState())
   | GoMenu => State.Menu;

