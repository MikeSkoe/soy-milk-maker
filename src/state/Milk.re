type t = {
   source: Product.t,
   time: float,
   id: int,
};

type milkMaker = 
  | NotBought
  | Bought(option(t));

type milkState =
   | Empty
   | Started
   | Half
   | Full
   | OutDated;

let state_of_milk = fun
   | {time} when time < 15.0 => Empty
   | {time} when time < 30.0 => Started
   | {time} when time < 45.0 => Half
   | {time} when time > 60.0 => OutDated
   | _ => Full;

let make = (~source, ~time=0.0, ~id=Random.int(999), ()) =>  {source, time, id}

let price_of_milk = milk => switch (state_of_milk(milk)) {
   | Empty => 0
   | Full => milk.source
      |> Product.price_of_product
      |> (*)(2)
   | OutDated => -(Product.price_of_product(milk.source) * 2)
   | _ => milk.time |> int_of_float
};