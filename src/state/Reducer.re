type action =
    | Tick
    | Buy(Product.t)
    | Sell(Milk.t)
    | Restart
    | GoMenu
    | GoGame;

let tick = (state: State.t): State.t => switch state {
  | Menu => state
  | Game(gameState) => Game({
    ...gameState,
    milks: List.map((milk: Milk.t): Milk.t => {...milk, time: milk.time +. 0.1}, gameState.milks),
  })
};

let buy_product = (
    state: State.t,
    product,
): State.t => switch state {
  | Menu => state
  | Game(gameState) => switch (
      gameState.milks |> List.exists((milk: Milk.t) => milk.source == product),
      gameState.money >= Product.price_of_product(product),
  ) {
      | (false, true) => Game({
          ...gameState,
          money: gameState.money - Product.price_of_product(product),
          milks: gameState.milks @ [Milk.make(~source=product, ())],
      })
      | (_, _) => state
  }
};

let sell_milk = (
  state: State.t,
  milk: Milk.t,
): State.t => switch state {
  | Menu => state
  | Game(gameState) => {
    print_endline(milk.id |> string_of_int);

    Game({
      ...gameState,
      money: gameState.money
          + Milk.price_of_milk(milk),
      milks: gameState.milks
          |> List.filter((m: Milk.t) => m.source !== milk.source)
    });
  }
};

let reducer = (state: State.t, action): State.t => switch action {
  | Tick => tick(state)
  | Buy(product) => buy_product(state, product)
  | Sell(milk) => sell_milk(state, milk)
  | Restart => Game(State.makeGameState())
  | GoGame => Game(State.makeGameState())
  | GoMenu => Menu
};

