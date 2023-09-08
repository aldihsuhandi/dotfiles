I've created an install script to install the necessary packages, it uses paru as an AUR helper if you want, you can change it to AUR helper of your preferences<br>
You also need to add an environment variables to make sure the theming work for qt applications.

```bash
QT_QPA_PLATFORMTHEME=qt5ct
```

You also need copy the .fonts file to your home directory and run

```bash
fc-cache -fv
```
to install all the fonts used in this config.


## IMAGE
![img](images/dracula.png)
