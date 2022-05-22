# Morse Generator

## Compile

### Text to Morse
```shell
make t2m
```

### Morse to Text
```shell
make m2t
```

## Run

### Text to Morse
```shell
./t2m "infile" -o "outfile"
```

### Morse to Text
```shell
./m2t "infile"
```

You can choose between iterative [i] and recursive [r] mode:
```shell
./m2t "infile" -m i
```
or
```shell
./mt2 "infile" -m r
```

There is also the option to input text directly with `-t "input"`.