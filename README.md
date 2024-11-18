# 🍽️ La Grande Restaurant Management System

![Restaurant Management](https://img.shields.io/badge/Restaurant-Management-orange)
![Version](https://img.shields.io/badge/Version-1.0-blue)
![License](https://img.shields.io/badge/License-MIT-green)

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [System Requirements](#system-requirements)
- [Data Structure](#data-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Screenshots](#screenshots)
- [Contributing](#contributing)
- [License](#license)

## 🎯 Overview
La Grande Restaurant Management System is a comprehensive solution designed to streamline restaurant operations, from order management to financial reporting. Built using a multilist data structure, this system efficiently handles multiple concurrent orders while maintaining data integrity.

## ⭐ Features

### 🧾 Order Management
- Create new orders with table assignments
- Add/modify menu items in existing orders
- Real-time order tracking
- Print order receipts

### 💳 Payment Processing
- **Merge Orders**: Combine multiple orders for group payments
- **Split Bills**: Divide a single order into multiple bills
- Secure payment validation
- Change calculation

### 📊 Reporting
- Daily revenue tracking
- Most popular menu items analysis
- Sales trends visualization
- Custom period reports

### 💾 Data Persistence
- Auto-save functionality
- Data backup and restore
- Export reports to files

## 🖥️ System Requirements
- C Compiler (GCC recommended)
- Minimum 2GB RAM
- 100MB free disk space
- Terminal/Command Prompt

## 🏗️ Data Structure

### Main Components
```
Multilist
└── Order (Parent)
    ├── Order Details
    │   ├── Order Number
    │   ├── Date
    │   ├── Table Number
    │   └── Total Amount
    │
    └── Menu Items (Child)
        ├── Item Name
        ├── Quantity
        ├── Price
        └── Subtotal
```

### Key Relationships
| Entity | Relationship | Entity |
|--------|-------------|--------|
| Order | 1:N | Menu Items |
| Order | 1:1 | Merged Order |

## 🚀 Installation

1. Clone the repository
```bash
git clone https://github.com/username/la-grande-system.git
```

2. Navigate to project directory
```bash
cd la-grande-system
```

3. Compile the program
```bash
gcc -o restaurant main.c
```

4. Run the application
```bash
./restaurant
```

## 🎮 Usage

### Creating a New Order
```c
DataParent orderData = makeDataParent(1, "2024-03-18", 5);
insertFirstParent(&restaurantSystem, orderData);
```

### Adding Menu Items
```c
DataChild itemData = makeDataChild("Pasta Carbonara", 2, 15.99);
insertLastChild(restaurantSystem, 1, itemData);
```

### Processing Payment
```c
prosesPayment(&restaurantSystem, orderNumber, paymentAmount);
```

## 📸 Screenshots

<details>
<summary>Click to view screenshots</summary>

### Main Menu
```
===== La Grande Restaurant =====
1. Create New Order
2. Add Menu Items
3. Process Payment
4. View Reports
5. Exit
```

### Order Management
```
Order #1234
Table: 5
Items:
- 2x Pasta Carbonara   $31.98
- 1x Caesar Salad      $12.99
Total: $44.97
```
</details>

## 🤝 Contributing
We welcome contributions! Please follow these steps:

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

<div align="center">

Made with ❤️ by LaGrande Team

📧 Contact: admin@lagranade.com

---
