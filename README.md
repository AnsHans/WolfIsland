[![](https://i.imgur.com/WBBV3fU.jpg)](#)

# Overview:
Simple simulation made in Qt framework using C++. It's extended version of game of life.

# Details:
To add objects press r for rabbit, f for wolf female, m for wolf male, g for hedge.
The project simulates grid with wolves and rabbits. 
Rabbits are moving with the same propability on each cell. Each rabbit has 20% propability to clone.
Wolves have two genders, male and female. If there is rabbit near a wolf then It starts to chase it.
If it catches a rabbit then gains 1 body fat, otherwise loses 0.1. If there is female and male wolf on a same cell
then they have a child, gender is random.
