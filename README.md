# `team-generator`: A team maker for an optimal gameplay

Given mmr(Match Making Rating) of each players, this program generates a team that is optimal in the sense that the difference between the maximum and the minimum of sum of each team is the smallest.

## Prerequisites

The current project is known to compile with `g++ 10.2.0` under `Ubuntu 20.04`.

## Compile
First, open the terminal and clone the repository.
If you don't have git installed, just download the code from the [github repo](https://github.com/OFCT-Devs/ofct-matchbot).
```shell script
git clone https://github.com/OFCT-Devs/team-generator.git
```

In directory `team-generator`, follow the instructions written in [or-tools installation guide](https://developers.google.com/optimization/install/cpp/linux#ubuntu-20.04-lts).
The extracted folder should be in the directory `team-generator`.
Also, rename the folder as `or-tools`.

## Run

1. In the directory `team-generator`, open the terminal and run the following command.
This will initialize the environment.
```shell script
sh init.sh
```

2. Make a file `user.csv` under the directory `team-generator`.
This file contains number of teams, number of people in each team, and user informations.
```shell script
touch user.csv
```

3. Modify the file using `gedit`, `LibreOffice Calc`, or anything else you are used to.
The resulting `user.csv` should be formatted as below.
- `M` is the number of people in each team, and `N` is the number of teams.
- `user(n)_name` is the user's name.
- `user(n)_mmr` denotes the user's mmr, or some kind of user's ability, which should be an integer.
```text
M,N
user1_name,user1_mmr
user2_name,user2_mmr
...
userMN_name,userMN_mmr
```

4. Now run `build.sh`.
If you followed the above instructions correctly, you will get a new file `out.csv`, which is formatted as below.
```text
team 1,,team 2,, ... ,,team N,,
usera1_name,usera1_mmr,userb1_name,userb1_mmr, ... ,userN1_name,userN1_mmr,
usera2_name,usera2_mmr,userb2_name,userb2_mmr, ... ,userN2_name,userN2_mmr,
...
useraM_name,useraM_mmr,userbM_name,userbM_mmr, ... ,userNM_name,userNM_mmr,
,team 1 sum,,team 2 sum,, ... ,,team N sum,
```
