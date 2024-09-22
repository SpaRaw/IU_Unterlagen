const express = require('express');
const mysql = require('mysql2');
const util = require('util'); // Für asynchrone Abfragen

const app = express();
const PORT = 3000;

// MySQL-Datenbankverbindung
const connection = mysql.createConnection({
    host: '127.0.0.1',
    user: 'root',
    password: 'root',
    database: 'saphire',
    port: '3306'
});

// Promisify für asynchrone Nutzung
const query = util.promisify(connection.query).bind(connection);

// Synchronous Endpunkt
app.get('/api/synchron', (req, res) => {
    // MySQL-Abfrage wird synchron durchgeführt
    connection.query(`
      SELECT Company, Product, TypeName, CPU_company, CPU_model, Price_euros 
      FROM laptop_prices 
      WHERE Price_euros BETWEEN 500 AND 2000
      LIMIT 10;`,
        (error, results) => {
            if (error) {
                res.status(500).send("Fehler bei der Datenbankabfrage: " + error);
            } else {
                res.json(results);  // Sendet die synchron geladenen Daten
            }
        });
});

// Asynchronous Endpunkt
app.get('/api/asynchron', async (req, res) => {
    try {
        // MySQL-Abfrage wird asynchron mit async/await durchgeführt
        const results = await query(`
          SELECT Company, Product, TypeName, CPU_company, CPU_model, Price_euros 
          FROM laptop_prices 
          WHERE Price_euros BETWEEN 500 AND 2000
          LIMIT 10;
        `);
        res.json(results);  // Sendet die asynchron geladenen Daten
    } catch (error) {
        res.status(500).send("Fehler bei der Datenbankabfrage: " + error);
    }
});

app.listen(PORT, (error) => {
    if (!error) {
        console.log("Server is Successfully Running, and App is listening on port " + PORT);
    } else {
        console.log("Error occurred, server can't start", error);
    }
});