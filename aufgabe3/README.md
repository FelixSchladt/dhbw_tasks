# Morse Generator

## Compile

### Text to Morse
```shell
make text2morse
```

### Morse to Text
```shell
make morse2text
```

## Run

### Text to Morse
```shell
./text2morse "infile" -o "outfile"
```

### Morse to Text
```shell
./morse2text "infile"
```

You can choose between iterative [i] and recursive [r] mode:
```shell
./morse2text "infile" -m i
```
or
```shell
./morse2text "infile" -m r
```

There is also the option to input text directly with `-t "input"`.