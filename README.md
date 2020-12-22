[![](https://i.imgur.com/WBBV3fU.jpg)](#)

# Overview:
Simple simulation made in Qt framework using C++. It's an extended version of the game of life.

# Details:
To add objects press r for rabbit, f for wolf female, m for wolf male, g for hedge. The project simulates a grid with wolves and rabbits. Rabbits are moving with the same probability on each cell. Each rabbit has a 20% probability to clone. Wolves have two genders, male and female. If there is a rabbit near a wolf then It starts to chase it. If it catches a rabbit then gains 1 body fat, otherwise loses 0.1. If there is a female and male wolf on the same cell then they have a child, gender is random.

