open Reprocessing;
open State;

type productButton = {
    product: State.product,
    pos: (int, int),
    size: (int, int),
}

let makeProductButton = (
    index: int,
    product: State.product,
) => {
    product,
    pos: (index * 100 + 100, 100),
    size: (75, 20),
};

let buttons: list(productButton)
    = [Soy, Nut, Coconut]
    |> List.mapi(makeProductButton)
;

let draw = (state, env) => {
    buttons
        |> List.iter(button => {
            let (width, height) = button.size;

            Draw.rect(~pos=button.pos, ~width, ~height, env);
        });

    state;
}

let mouseDown = (state: State.t, env) => {
    let mousePos = Env.mouse(env);
    let clickedProducts
        = buttons
        |> List.filter(button => 
            Collisions.rect_point(
                ~rectPos=button.pos,
                ~rectSize=button.size,
                ~point=mousePos,
            )
        );
    
    print_endline(
        List.length(clickedProducts)
            |> string_of_int
    );
    switch clickedProducts {
        | [first, ..._] => {
            let state = Reducer.reducer(state, Buy(first.product));
            print_endline(string_of_int(state.money));

            state;
        }
        | [] => state
    };
}

let update = (state: State.t, env) => {
    state
}