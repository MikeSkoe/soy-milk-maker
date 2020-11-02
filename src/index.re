open Reprocessing;

let setup = env => {
  Env.size(~width=600, ~height=600, env);

  State.make()
};

let draw = (state, env) =>
  state
    |> GameScene.update(_, env)
    |> GameScene.draw(_, env);
  
let mouseDown = (state, env) =>
  state
    |> GameScene.mouseDown(_, env);

let keyPressed = (state, env) =>
  state
    |> GameScene.keyPressed(_, env);

run(~setup, ~draw, ~mouseDown, ~keyPressed, ());
