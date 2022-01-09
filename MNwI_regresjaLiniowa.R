# Program: MNwI_regresjaLiniowa, 21.11.2021
# Autor: Szynal Lukasz, 150063, 2021 / 2022, Informatyka, D2, II semestr

# Analiza zależności PM2.5 od temperatury na podstawie danych z Amasady USA w Pekinie.

# Instalujemy wymagane bilbioteki
if (!require("ggplot2")) {
    install.packages("ggplot2")
}
if (!require("tidyverse")) {
    install.packages("tidyverse")
}
if (!require("readxl")) {
    install.packages("readxl")
}

# Wczytujemy wymagane bilbioteki
library("ggplot2")
library(tidyverse)
library(readxl)

# Pobieramy zbiór danych. Godzinowy zestaw zawierający dane o PM2,5 z ambasady USA w Pekinie
PM2.5_Pekin <- read.table(file = "https://archive.ics.uci.edu/ml/machine-learning-databases/00381/PRSA_data_2010.1.1-2014.12.31.csv",
          sep = ",", header = TRUE)

# Podsumowanie pobranych danych
summary(PM2.5_Pekin)
# Na podstawie podsumowania określamy zakres wykresu biorąc pod uwagę maksymalne i minimalne wartości PM2.5 oraz TEMP
# Odpowiednie (-19, 42) dla temperatury oraz (0, 994) dla PM2.5

# Wyświetlamy wykres zależności zanieczyszczen pm 2.5 od temperatury
ggplot(PM2.5_Pekin, aes(x = TEMP, y = pm2.5)) +
    geom_point(colour = "blue", size = 1) +
    geom_smooth(method = "lm", colour = "red", size = 2) +
    xlab("Temperatura") +
    ylab("PM 2.5") +
    xlim(-19, 42) +
    ylim(0, 994) +
    theme_bw()

# Modelowanie rozpoczynamy od określenia zmiennej zależnej i niezależnej.
PM2.5_model <- lm(formula = pm2.5 ~ TEMP, data = PM2.5_Pekin)
summary(PM2.5_model)
# Na podstawie otrzymanego wyniku dokonujemy interpretacji parametrów.
# Wzrost temperatury o 1 stopień powoduje spadek zanieczyszczeń PM2.5 o -0.68448
# Wartości obliczone na podstawie modelu różnią się od rzeczywistości średnio o +/- 91.67

# Prognozujemy wartość PM2.5 dla temperatur: -10, 0, 10, 20, 30
prognozaZanieczyszczen <- data.frame(TEMP = c(-10, 0, 10, 20, 30))
prognozaZanieczyszczen <- prognozaZanieczyszczen %>%
    mutate(PM2.5_pred = predict(object = PM2.5_model, newdata = .))

prognozaZanieczyszczen
#  TEMP PM2.5_pred
#1 -10  113.94663 +/- 91.67
#2   0  107.10183 +/- 91.67
#3  10  100.25704 +/- 91.67
#4  20  93.41224 +/- 91.67
#5  30  86.56744 +/- 91.67
