type action =
   | Tick
   | Buy(Product.t)
   | Sell(Milk.t)
   | BuyMilkMaker;

let tick = (gameState: State.gameState) => {
   ...gameState,
   milkMakers: gameState.milkMakers
      |> List.map((milkMaker: Milk.milkMaker) => switch milkMaker {
         | Milk.Bought(Some(milk)) => Milk.Bought(Some({
            ...milk,
            time: milk.time +. 0.1,
         }))
         | _ => milkMaker
      }),
};

let setElementAt = (~index: int, ~value: 'a, theList: list('a)) =>
   List.mapi(
      (i,x) => if (i==index) value else x,
      theList
   );

let findMilkMakerIndex = (checkMilkMaker: (Milk.milkMaker) => bool, milkMakers: list(Milk.milkMaker)) => {
   let (found, _) = milkMakers
      |> List.fold_left(
         ((found, index), curr: Milk.milkMaker) => {
            switch (found, index, curr) {
            | (-1, index, milkMaker) when checkMilkMaker(milkMaker) => (index, index + 1)
            | (_, _, _) => (found, index + 1)
            }
         },
         (-1, 0),
      );

   found;
};

let findEmptyMilkMaker = findMilkMakerIndex(fun
   | Milk.Bought(None) => true
   | _ => false
);

let findNotBoughtMilkMaker = findMilkMakerIndex(fun
   | Milk.NotBought => true
   | _ => false
);

let buy_product = (
   gameState: State.gameState,
   product: Product.t,
) => switch (
   gameState.money >= Product.price_of_product(product),
) {
   | true => {
      let found = findEmptyMilkMaker(gameState.milkMakers)
      
      switch found {
         | -1 => gameState
         | foundIndex => {
            ...gameState,
            money: gameState.money - Product.price_of_product(product),
            milkMakers: gameState.milkMakers
               |> List.mapi((index, milkMaker: Milk.milkMaker) => switch (index, milkMaker) {
                  | (index, Bought(None)) when index == foundIndex =>
                     Milk.Bought(
                        Some(Milk.make(~source=product, ()))
                     )
                  | (_, _) => milkMaker
               })
         }
      }
   }
   | false => gameState
};

let sell_milk = (
   gameState: State.gameState,
   selledMilk: Milk.t,
) => {
   ...gameState,
   money: gameState.money
      + Milk.price_of_milk(selledMilk),
   milkMakers: gameState.milkMakers
      |> List.map((milkMaker: Milk.milkMaker) => switch milkMaker {
         | Bought(Some(milk)) when milk.id == selledMilk.id => Milk.Bought(None)
         | _ => milkMaker
      })
};

let buy_milk_maker = (
   gameState: State.gameState,
) => {
   let found = findNotBoughtMilkMaker(gameState.milkMakers);

   switch (found, gameState.money) {
      | (-1, _) => gameState
      | (_, money) when money < 100 => gameState
      | (foundIndex, money) => {
         ...gameState,
         money: money - 100,
         milkMakers: gameState.milkMakers
            |> List.mapi(
               (index, milkMaker) => switch index {
                  | index when index == foundIndex => Milk.Bought(None)
                  | _ => milkMaker
               }
            )
      }
   }
}

let dispatch = gameState => fun
   | Tick => tick(gameState)
   | Buy(product) => buy_product(gameState, product)
   | Sell(milk) => sell_milk(gameState, milk)
   | BuyMilkMaker => buy_milk_maker(gameState);
