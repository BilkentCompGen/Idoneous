# 0. Installation

To install Linden, first you should fetch it from our git repository, or download one of the corresponding compressed zip/tar.gz packages. After downloading, change the current directory to the source directory `Linden`, and run `make` in the terminal. The `linden` binary will be created, which are ready to use.

```bash
git clone https://github.com/BilkentCompGen/Linden/
cd Linden
make build
```
----
# 1. Running Linden Tool

In order to make alignment between two genomes, namely `genome1.fasta` and `genome2.fasta` you need to run following commands. This command will create the file `alignment.out`.

```bash
$ ./linden -s1=genome1.fasta -s2=genome2.fasta > alignment.out
```
Linden depends on the following parameters:

– **block size (b):** minimum size of an inner node in the ALFTree. If the size of a node is smaller than b then it is a leaf node.
– **chaining threshold (c):** minimum number of seeds required to build a valid chain.
– **division length (d):** approximate distance between the starting positions of two intervals in a sequence.
– **division window (a):** number of divisions traversed in one matching step.
– **max indel rate (e):** maximum indel rate (used as 1/e) between two link lengths, where a link length corresponds to the distance between two consecutive seeds.
– **k-mer size (k):** length of k-mers at the starting positions of the blocks for comparisons


By default, linden uses following parameter values.
a = 2
b = 2000
c = 2
d = 8000
e = 200
k = 2

In order to change the parameter values, you can use following command.
For  example, following command changes the value of a to 7.
```bash
$ ./linden -s1=genome1.fasta -s2=genome2.fasta -a=7 > alignment.out
```
Another example which sets b to 4000 and c to 5 is:
```bash
$ ./linden -s1=genome1.fasta -s2=genome2.fasta -b=4000 -c=5 > alignment.out
```
