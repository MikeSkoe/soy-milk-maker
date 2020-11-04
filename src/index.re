open State;
open Reprocessing;

let setup = env => {
   Env.size(~width=600, ~height=600, env);

   State.make();
};

let draw = (state: State.t, env) => switch state {
   | Menu =>
      state
         |> MenuScene.update(env)
         |> MenuScene.draw(env)
   | Game(gameState) => 
      gameState
         |> GameScene.update(env)
         |> GameScene.draw(env)
         |> State.makeGame
}

let mouseDown = (state, env) => switch state {
   | Menu =>
      state
         |> MenuScene.mouseDown(env)
   | Game(gameState) => 
      gameState
         |> GameScene.mouseDown(env)
         |> State.makeGame;
}

let keyPressed = (state, env) => switch (Env.keyCode(env)) {
   | G => Reducer.dispatch(state, GoGame)
   | M => Reducer.dispatch(state, GoMenu)
   | _ => switch state {
      | Menu =>
         state
            |> MenuScene.keyPressed(env)
      | Game(gameState) => 
         gameState
            |> GameScene.keyPressed(env)
            |> State.makeGame;
   }
}

run(~setup, ~draw, ~mouseDown, ~keyPressed, ());
