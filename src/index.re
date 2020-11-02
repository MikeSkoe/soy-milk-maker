open Reprocessing;

let setup = env => {
  Env.size(~width=600, ~height=600, env);

  State.make()
};

let mouseDown = (state, env) => {
  state
    |> ProductList.mouseDown(_, env);
}

let update = (state, env) => {

  state
    |> ProductList.update(_, env);
};

let draw = (state, env) => {

  state
    |> ProductList.draw(_, env);
};

let tick = (state, env) => {
  Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
  Draw.fill(Constants.black, env);

  state
    |> update(_, env)
    |> draw(_, env);
};

run(~setup, ~draw=tick, ~mouseDown, ());
