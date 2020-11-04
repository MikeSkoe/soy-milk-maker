type gameState = {
   bought: list(Product.t),
   milks: list(Milk.t),
   money: int,
};

let makeGameState = () => {
   bought: [],
   milks: [],
   money: 150,
};

type t =
   | Game(gameState)
   | Menu;

let make = () => Game(makeGameState());

let makeGame = gameState => Game(gameState);
