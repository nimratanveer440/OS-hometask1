import express from'express'
const app = express()
function handler (request, response){
    response.send("Hello World")
}
app.get('/', handler)
app.listen(3000)