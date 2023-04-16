class Image():
    def __init__(self, format='P3', rows=0, columns=0, max_value=255, pixels=[[]]):
        self.format = format
        self.rows = rows
        self.columns = columns
        self.max_value = max_value
        self.pixels = pixels
    def __str__(self):
        # use this for debugging
        image = ""
        image += f"{self.format}\n{self.rows} {self.columns}\n{self.max_value}\n"
        for i in range(self.rows):
            for j in range(3 * self.columns):
                image += f"{self.pixels[i][j]} "
            image += "\n"
        #print(image)
        return image
    def sepia(self):
        # apply sepia filter to the image
        x = self.columns * 3
        j = 0
        for i in range(self.rows):
            j = 0
            while j < x:
                sepia_r = (int)(0.393*self.pixels[i][j] + 0.769*self.pixels[i][j+1] + 0.189*self.pixels[i][j+2])
                sepia_g = (int)(0.349*self.pixels[i][j] + 0.686*self.pixels[i][j+1] + 0.168*self.pixels[i][j+2])
                sepia_b = (int)(0.272*self.pixels[i][j] + 0.534*self.pixels[i][j+1] + 0.131*self.pixels[i][j+2])
                if sepia_r > 255: #dupa lungi si ingrozitoare lupte seculare --tot nu sunt de acord cu chestia asta scz
                    sepia_r = 255
                if sepia_g > 255:
                    sepia_g = 255
                if sepia_b > 255:
                    sepia_b = 255
                self.pixels[i][j] = sepia_r 
                self.pixels[i][j+1] = sepia_g 
                self.pixels[i][j+2] = sepia_b 
                j = j+3

    def read(self, filename):
        # read from file and assign the correct parameters (see README and input examples)
        f = open(filename,"r")
        self.format = f.readline().strip() #scot endl e strcspn din c
        size = f.readline().split()
        self.rows =int(size[0])  #readline returns string....
        self.columns = int(size[1])
        max = f.readline().split()
        self.max_value = int(max[0])
        #print("aici e column: ", self.columns)
        self.pixels = [[0 for j in range(3*self.columns)] for i in range(self.rows)] #daca nu initializez face ca drq
        #num_columns = len(self.pixels[0])
        #print("3 ori col:",num_columns)
        for i in range(self.rows):
            linie = f.readline().split()
            x = self.columns * 3
            j = 0
            while j < x:
                self.pixels[i][j] =int(linie[j])
                j = j + 1
        f.close()
    def write(self, filename):
        # write to file in the correct format (see README and input examples)
        f = open(filename,"w")
        f.write(f"{self.format}\n{self.rows} {self.columns}\n{self.max_value}\n")
        x = self.columns *3
        for i in range(self.rows):
            for j in range(x):
                f.write(f"{self.pixels[i][j]}")
                #ca sa scrii spatiu verifici daca e egal cu nr de coloane --ultimul canal
                if j != x:
                    f.write(" ")
            f.write("\n")
        f.close()
