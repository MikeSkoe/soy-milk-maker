let mouseDown = (env, gameState: State.gameState) =>
   gameState
      |> ProductList.mouseDown(env)
      |> MilkList.mouseDown(env);

let update = (env, gameState: State.gameState) => 
   gameState
      |> ProductList.update(env)
      |> MilkList.update(env);

let keyPressed = (env, gameState: State.gameState) => 
   gameState;

let draw = (env, image: Reprocessing.imageT, gameState: State.gameState) => {
   Stats.draw(env, gameState);
   ProductList.draw(env, image, gameState);
   MilkList.draw(env, image, gameState);

   gameState;
}
