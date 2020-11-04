let mouseDown = (env, gameState) =>
   gameState
      |> ProductList.mouseDown(env)
      |> MilkList.mouseDown(env);

let update = (env, gameState) => 
   gameState
      |> ProductList.update(env)
      |> MilkList.update(env);

let keyPressed = (env, gameState: State.gameState) => 
   gameState;

let draw = (env, gameState) => {
   Stats.draw(env, gameState);
   ProductList.draw(env, gameState);
   MilkList.draw(env, gameState);

   gameState;
}
