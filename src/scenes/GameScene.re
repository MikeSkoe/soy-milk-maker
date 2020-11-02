let mouseDown = (state, env) =>
  state
    |> ProductList.mouseDown(_, env)
    |> MilkList.mouseDown(_, env);

let update = (state, env) => 
  state
    |> ProductList.update(_, env)
    |> MilkList.update(_, env);

let draw = (state, env) =>
  state
    |> Stats.draw(_, env)
    |> ProductList.draw(_, env)
    |> MilkList.draw(_, env);

let keyPressed = (state, env) => 
  state
    |> Stats.keyPressed(_, env);
