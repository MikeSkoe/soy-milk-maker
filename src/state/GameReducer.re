type action =
   | Tick
   | Buy(Product.t)
   | Sell(Milk.t);

let tick = (gameState: State.gameState) => {
   ...gameState,
   milks: gameState.milks
      |> List.map((milk: Milk.t): Milk.t => {...milk, time: milk.time +. 0.1}),
};

let buy_product = (
   gameState: State.gameState,
   product: Product.t,
) => switch (
   gameState.milks |> List.exists((milk: Milk.t) => milk.source == product),
   gameState.money >= Product.price_of_product(product),
) {
   | (false, true) => {
      ...gameState,
      money: gameState.money - Product.price_of_product(product),
      milks: gameState.milks @ [Milk.make(~source=product, ())],
   }
   | (_, _) => gameState
};

let sell_milk = (
   gameState: State.gameState,
   milk: Milk.t,
) => {
   ...gameState,
   money: gameState.money
      + Milk.price_of_milk(milk),
   milks: gameState.milks
      |> List.filter((m: Milk.t) => m.source !== milk.source)
};

let dispatch = gameState => fun
   | Tick => tick(gameState)
   | Buy(product) => buy_product(gameState, product)
   | Sell(milk) => sell_milk(gameState, milk);
