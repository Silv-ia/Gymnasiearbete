# Gymnasiearbete inom linjen produktionsteknik
###### "Mekanisk dansare: Den dansande robotarmen Lilith"

Ett projekt där vi designade, konstruerade och programmerade en robotarm. Projektet grundades i gruppens bakgrund inom dans och en vilja att kombinera estetik med teknik. Syftet var att bygga roboten från grunden och programmera den så att den kunde röra sig till musik.

Mitt ansvar var programmering och all kod är skriven via Arduino.
Skrivet själv, med hjälp av https://www.arduino.cc/reference/en/.

Roboten styrs med hjälp av servomotorer, både kontinuerliga (som kan snurra i olika hastighet i båda riktningar med hastighet och riktning som styrmedel) och vinklade (rörlighet begränsad till 180 grader styrd av vinkel). Detta krävde två olika metoder för att uppdatera motorernas rörelse. 
Sedan skulle rörelserna anpassas till olika låtars hastighet, så rörelserna behövde ta hänsyn till en låts bpm (beats per minute).

Syftet med koden var att försöka generalisera lösningarna för att hantera olika typer av motorer och olika typer av låter. Samt enkelt tillåta ändring av koreografi genom att använda listor för olika värden på vinkel, hastighet och riktning. 
