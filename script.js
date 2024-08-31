class MagicSquare {
    constructor() {
        this.n = 16;
        this.arr = Array.from({ length: this.n }, (_, i) =>
            Array.from({ length: this.n }, (_, j) => this.n * i + j + 1)
        );
    }

    applyKey(key) {
        const randomSeed = this.hashKey(key);

        // Randomly shuffle the magic square using the key-based seed
        for (let i = 0; i < this.n; i++) {
            for (let j = 0; j < this.n; j++) {
                let randIndex1 = (i * randomSeed + j) % this.n;
                let randIndex2 = (j * randomSeed + i) % this.n;
                [this.arr[i][j], this.arr[randIndex1][randIndex2]] = [this.arr[randIndex1][randIndex2], this.arr[i][j]];
            }
        }
    }

    hashKey(key) {
        // Simple hash function to convert the key to a numeric seed
        let hash = 0;
        for (let i = 0; i < key.length; i++) {
            hash = (hash << 5) - hash + key.charCodeAt(i);
            hash |= 0; // Convert to 32bit integer
        }
        return Math.abs(hash) % 100; // Keep it within a reasonable range
    }

    printSquare() {
        const container = document.getElementById("magic-square");
        container.innerHTML = "";
        for (let i = 0; i < this.n; i++) {
            for (let j = 0; j < this.n; j++) {
                const cell = document.createElement("div");
                cell.className = "cell";
                cell.textContent = this.arr[i][j];
                container.appendChild(cell);
            }
        }
    }

    getCellValue(i, j) {
        return this.arr[i][j];
    }
}

class Encryptor {
    constructor(magicSquare) {
        this.map = new Map();
        for (let i = 0; i < 16; i++) {
            for (let j = 0; j < 16; j++) {
                let key = i.toString().padStart(2, '0') + j.toString().padStart(2, '0');
                let char = String.fromCharCode(magicSquare.getCellValue(i, j) % 256);
                this.map.set(char, key);
            }
        }
    }

    encrypt(message) {
        return Array.from(message).map(char => this.map.get(char)).join('');
    }
}

class Decryptor {
    constructor(magicSquare) {
        this.map = new Map();
        for (let i = 0; i < 16; i++) {
            for (let j = 0; j < 16; j++) {
                let key = i.toString().padStart(2, '0') + j.toString().padStart(2, '0');
                let char = String.fromCharCode(magicSquare.getCellValue(i, j) % 256);
                this.map.set(key, char);
            }
        }
    }

    decrypt(ciphertext) {
        let plaintext = "";
        for (let i = 0; i < ciphertext.length; i += 4) {
            let key = ciphertext.slice(i, i + 4);
            plaintext += this.map.get(key);
        }
        return plaintext;
    }
}

function encryptMessage() {
    const key = document.getElementById("key").value;
    const message = document.getElementById("message").value;

    if (!key) {
        alert("Please enter a key.");
        return;
    }

    if (!message) {
        alert("Please enter a message.");
        return;
    }

    const magicSquare = new MagicSquare();
    magicSquare.applyKey(key);
    magicSquare.printSquare();

    const encryptor = new Encryptor(magicSquare);
    const ciphertext = encryptor.encrypt(message);
    document.getElementById("ciphertext").textContent = ciphertext;

    const decryptor = new Decryptor(magicSquare);
    const plaintext = decryptor.decrypt(ciphertext);
    document.getElementById("plaintext").textContent = plaintext;
}
