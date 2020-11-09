open State;

type globalAction =
   | GoGame
   | GoMenu;

let dispatch = (state: State.t, action: globalAction): State.t => switch action {
| GoGame => {...state, scene: Game(State.makeGameState())}
| GoMenu => {...state, scene: Menu}
};
