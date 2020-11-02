open Reprocessing;

let setup = env => {
  Env.size(~width=600, ~height=600, env);

  State.make()
};

let mouseDown = (state, env) =>
  state
    |> ProductList.mouseDown(_, env)
    |> MilkList.mouseDown(_, env);

let update = (state, env) => 
  state
    |> ProductList.update(_, env)
    |> MilkList.update(_, env);

let draw = (state: State.t, env) =>
  state
    |> Stats.draw(_, env)
    |> ProductList.draw(_, env)
    |> MilkList.draw(_, env);

let tick = (state, env) =>
  state
    |> update(_, env)
    |> draw(_, env);

let keyPressed = (state, env) => 
  state
    |> Stats.keyPressed(_, env);

run(~setup, ~draw=tick, ~mouseDown, ~keyPressed, ());
