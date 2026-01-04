import express from "express";
import mongoose from "mongoose";
import cors from "cors";

const app = express();
const PORT = 3000;

// Middlewares
app.use(cors());
app.use(express.json());

// MongoDB URL (docker-compose se env aa jayega)
const MONGO_URL =
  process.env.MONGO_URL || "mongodb://mongodb:27017/guestbook";

// Schema
const messageSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true,
  },
  message: {
    type: String,
    required: true,
  },
  timestamp: {
    type: Date,
    default: Date.now,
  },
});

// Model
const Message = mongoose.model("Message", messageSchema);

// DB Connection
async function connectDB() {
  try {
    await mongoose.connect(MONGO_URL);
    console.log("✅ Connected to MongoDB");
  } catch (error) {
    console.error("❌ MongoDB connection error:", error);
    process.exit(1);
  }
}

// Routes
app.get("/api/messages", async (req, res) => {
  try {
    const messages = await Message.find()
      .sort({ timestamp: -1 })
      .limit(10);
    res.json(messages);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

app.post("/api/messages", async (req, res) => {
  try {
    const { name, message } = req.body;

    if (!name || !message) {
      return res.status(400).json({ error: "Name and message required" });
    }

    const newMessage = new Message({ name, message });
    await newMessage.save();

    res.status(201).json(newMessage);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
});

// Start Server
connectDB().then(() => {
  app.listen(PORT, () => {
    console.log(`🚀 Server running on port ${PORT}`);
  });
});
