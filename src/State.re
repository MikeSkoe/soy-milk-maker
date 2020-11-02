type product =
    | Soy
    | Nut
    | Coconut;

type milk = {
    source: product,
    time: int,
};

let makeMilk = (~source, ~time=0, ()) =>  {source, time}

type t = {
    bought: list(product),
    milks: list(milk),
    money: int,
}

let make = () => {
    bought: [],
    milks: [],
    money: 100,
};

let price_of_product = fun
    | Soy => 50
    | Nut => 100
    | Coconut => 150;

let price_of_milk = fun
    | {source, time} when time < 10 => price_of_product(source) + time
    | {source, time} => {
        let overcoocked = time - 10;
        let loss = overcoocked
            |> float_of_int
            |> (**)(2.0)
            |> int_of_float;

        price_of_product(source) + 10 - loss;
    };
