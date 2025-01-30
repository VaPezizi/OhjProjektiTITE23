# Vaatimus määrittely  

## Toiminnalliset vaatimukset  

    - Pelin käynnistyessä, ruudulle aukeaa aloitus valikko.  
    - Valikosta löytyy napit pelin aloitukselle, lopetukselle ja ruudun tilan vaihtamiselle.  
    - Pelaaja pystyy hiiren osoittimella painaa aloitus nappia, pelin aloittaakseen.  
    - Pelaaja pystyy hiiren osoittimella painaa lopetus nappia, pelin lopettamiseen.  
    - Pelaaja pystyy hiiren osoittimella painaa ruudun tilan vaihtamisnappia.  
    - Kun pelaaja painaa ruudun tilan vaihtamisnappia, ruudun tila vaihtuu kokoruudun ja ikkunatilan välillä.  
    - Kun pelaaja on painanut aloitus nappia, peli alkaa.  
    - Pelaajan aloittaessaan pelin, hän näkee pelihahmon pelimaailman keskellä, ylhäältäpäin kuvattuna.  
    - Pelissä on pikseli grafiikkaa hyödyntäen tehty maailma, ja oliot.  
    - Pelimaailmassa pelaajalla on näytön oikeassa yläreunassa käyttöliitymä, jossa näkyy nykyinen kokemuspistetaso.  
    - Pelimaailmassa pelaajalla on näytön vasemmassa yläreunassa käyttöliitymä, jossa näkyy pelaajan hallussa olevat aseet.   
    - Pelimaailmassa pelaajalla on näytön vasemmassa yläreunassa käyttöliitymä, jossa näkyy pelaajan nykyinen terveyspistemäärä.  
    - Pelimaailmassa pelaajalla on näytön keskiosassa yläreunassa numeroarvo, jossa näkyy pelin kesto.    
    - Pelissä on ajastin, jonka aika päivitetään näytön yläosassa olevaan numeroarvoon sekunnin välein.    
    - Pelin alussa pelaajalla on yksi ase.  
    - Pelaaja voi pelimaailmassa painaa "W" nappia, liikkuakseen ylöspäin pelimaailmassa.  
    - Pelaaja voi pelimaailmassa painaa "D" nappia, liikkuakseen oikeallepäin pelimaailmassa.      
    - Pelaaja voi pelimaailmassa painaa "S" nappia, liikkuakseen alaspäin pelimaailmassa.   
    - Pelaaja voi pelimaailmassa painaa "A" nappia, liikkuakseen vasemmallepäin pelimaailmassa.   
    - Pelaaja voi pelimaailmassa painaa "P" nappia, joka asettaa pelin "Pause" tilaan.  
    - Pause tilassa pelissä olevat objektit eivät liiku, eikä ajastin laske.  
    - Pelin alkamisen jälkeen, tietyin ajoin pelimaailmaan ilmestyy uusi vihollinen.  
    - Viholliset liikkuvat pelimaailmassa pelaajaa päin.  
    - Kun vihollinen on tarpeeksi lähellä pelaajaa, se pysähtyy.  
    - Kun vihollinen on pysähtynyt, sen kohdalle luodaan ammus, joka lentää pelaajan suuntaan.  
    - Kun vihollinen tai vihollisen hyökkäys osuu pelaajaan, hän menettää terveyspisteitä.  
    - Pelihahmon ollessa vihollisten lähellä, tietyin aikavälein, pelaaja käyttää automaattisesti asettansa.  
    - Pelaaja hyökkäyksen osuessa viholliseen, vihollinen katoaa pelimaailmasta.    
    - Vihollisen kadottua, vihollisen paikalle jää kokemuspisteitä antava objekti.  
    - Pelaaja voi kävellä kokemuspiste objektin läheltä, ja kerätä pisteen itsellensä.  
    - Kun pelaaja on tarpeeksi kerännyt kokemuspisteitä, hänen kokemustasonsa nousee.  
    - Jokainen kokemustaso vaatii enemmän kokemuspisteitä.  
    - Kokemustason noustessa näkyviin tulee valikko, jossa on kolme ase vaihtoehtoa.  
    - Pelaaja voi valikosta hiiren osoittimella valita haluamansa päivityksen nykyiseen aseeseen tai uuden aseen.  
    - Valikossa olevat vaihtoehdot tulevat satunnaisesti.  
    - Kun pelaajan terveyspisteet ovat liian alhaiset, hän häviää pelin.  
    - Pelaajan hävitessä, peli palaa takaisin alkuruutuun.  



## Ei-toiminnalliset vaatimukset  

    - Pelissä tulee olla "pää luokka" Game, jonka kautta peli koostuu.  
    - Pelin ohjelmoinnin tulee käyttää Olio ajattelua, muuta ei liian tiukasti.  
    - Ohjelmoinnissa tulee käytttä camelCase tyyliä muuttuja nimille.  
    - Luokkien nimet pitää olla isolla alkukirjaimella.  
    - Globaalit ja vakiot tulee olla kokonaan isoilla kirjaimilla.  
    - Pelin pitää olla hauska.   
    - Pelin pitää olla helppo ymmärtää.  
    - Peli tulee olemaan paikallisesti pelattava, ilman mitään verkkopelaus mahdollisuutta.  
    - Pelin suorituskyky tulee olla hyvä vähintään keskivertoisella toimistokoneella.  
    - Pelin suorituskyvyn tulee skaalautua tarpeeksi hyvin. Kun pelin lopussa vihollisia tulee paljon, pelin täytyy silti pyöriä hyvin.  
    - Peliin tulee olla suhteellisen helppoa lisätä uusia hahmoja, vihollisia, aseita ja karttoja.  
    - Peli tullaan kehittämään C++ ohjelmointikielellä, hyödyntäen "raylib" C kirjastoa.  
    - Pelin koodi tulee sisältää kommentteja, varsinkin triviaaleissa paikoissa.  
    - Pelin tulee toimia, ilman isompia ongelmia Windows ja Linux käyttöjärjestelmissä.
    - Pelin lähdekoodin kääntämiseen tulee olla ohjeet.  
