open Reprocessing;
open State;

let setup = env => {
   Env.size(~width=600, ~height=600, env);

   State.make(env);
};

let draw = (state: State.t, env) => switch state.scene {
   | Menu =>
      state
         |> MenuScene.update(env)
         |> MenuScene.draw(env)
   | Game(gameState) => 
      gameState
         |> GameScene.update(env)
         |> GameScene.draw(env, state.image)
         |> State.makeGame(state)
}

let mouseDown = (state, env) => switch state.scene {
   | Menu =>
      state
         |> MenuScene.mouseDown(env)
   | Game(gameState) => 
      gameState
         |> GameScene.mouseDown(env)
         |> State.makeGame(state);
}

let keyPressed = (state, env) => switch (Env.keyCode(env)) {
   | G => Reducer.dispatch(state, GoGame)
   | M => Reducer.dispatch(state, GoMenu)
   | _ => switch state.scene {
      | Menu =>
         state
            |> MenuScene.keyPressed(env)
      | Game(gameState) => 
         gameState
            |> GameScene.keyPressed(env)
            |> State.makeGame(state);
   }
}

run(~setup, ~draw, ~mouseDown, ~keyPressed, ());
