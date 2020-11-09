type gameState = {
   bought: list(Product.t),
   milkMakers: list(Milk.milkMaker),
   money: int,
};

let makeGameState = () => {
   bought: [],
   milkMakers: [
      Milk.Bought(None),
      Milk.NotBought,
      Milk.NotBought,
   ],
   money: 150,
};

type scene =
   | Game(gameState)
   | Menu;

type t = {
   image: Reprocessing.imageT,
   scene: scene,
};

let make = env => {
   image: Reprocessing.Draw.loadImage(~filename="assets/milk.png", ~isPixel=true, env),
   scene: Game(makeGameState()),
};

let makeGame = (state, gameState) => {
   ...state,
   scene: Game(gameState),
}
