open State;
open Reprocessing;

let setup = env => {
  Env.size(~width=600, ~height=600, env);

  State.make();
};

let draw = (state, env) => switch state {
  | Menu =>
    state
      |> MenuScene.update(_, env)
      |> MenuScene.draw(_, env)
  | Game(_) => 
    state
      |> GameScene.update(_, env)
      |> GameScene.draw(_, env)
}

let mouseDown = (state, env) => switch state {
  | Menu =>
    state
      |> MenuScene.mouseDown(_, env)
  | Game(_) => 
    state
      |> GameScene.mouseDown(_, env);
}

let keyPressed = (state, env) => switch state {
  | Menu =>
    state
      |> MenuScene.keyPressed(_, env)
  | Game(_) => 
    state
      |> GameScene.keyPressed(_, env)
}

run(~setup, ~draw, ~mouseDown, ~keyPressed, ());
