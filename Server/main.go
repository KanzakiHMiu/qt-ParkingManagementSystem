package main

import (
    "database/sql"
    "net/http"
    "regexp"
    "log"
    "github.com/gin-gonic/gin"
    _ "github.com/go-sql-driver/mysql"
    "golang.org/x/crypto/bcrypt"
)

type LoginRequest struct {
    Username string `json:"username"`
    Password string `json:"password"`
}

type UserLoginRequest struct {
    Phone    string `json:"phone"`
    Password string `json:"password"`
}

type UserRegisterRequest struct {
    Phone            string `json:"phone"`
    Password         string `json:"password"`
    RegistrationDate string `json:"registration_date"`
}

type UserInfo struct {
    Username sql.NullString `json:"-"`
    Password         string `json:"password"`
    RegistrationDate string `json:"registration_date"`
    CarPlate sql.NullString `json:"-"`
    Phone            string `json:"phone"`
    Email    sql.NullString `json:"-"`
    Avatar   sql.NullString `json:"-"`

    UsernameStr      string `json:"username"`
    CarPlateStr      string `json:"car_plate"`
    EmailStr         string `json:"email"`
    AvatarStr        string `json:"avatar"`
}

type UpdateUserInfoRequest struct {
    Phone    string `json:"phone"`
    Username string `json:"username"`
    Email    string `json:"email"`
    CarPlate string `json:"car_plate"`
    Avatar   string `json:"avatar"`
}

type ParkingSpot struct {
    SpotID      int    `json:"spot_id"`
    SpotNumber  string `json:"spot_number"`
    IsAvailable bool   `json:"is_available"`
}

type BookSpotRequest struct {
    SpotNumber int    `json:"spot_number"`
    Phone      string `json:"phone"`
}

type BillingHistory struct {
    BillID      int     `json:"bill_id"`
    UserID      int     `json:"user_id"`
    OrderID     int     `json:"order_id"`
    PaymentDate string  `json:"payment_date"`
    Amount      float64 `json:"amount"`
}

type WalletInfo struct {
    WalletID         int             `json:"wallet_id"`
    UserID           int             `json:"user_id"`
    Balance          float64         `json:"balance"`
    LastRechargeDate sql.NullString  `json:"last_recharge_date"`
    AutoPayment      bool            `json:"auto_payment"`
}

type RechargeRequest struct {
    Phone            string  `json:"phone"`
    Amount           float64 `json:"amount"`
    LastRechargeDate string  `json:"last_recharge_date"`
}

func main() {
    dsn := "root:youmumoe.2@tcp(127.0.0.1:3306)/parking_management_system"
    db, err := sql.Open("mysql", dsn)
    if err != nil {
        log.Fatal(err)
    }
    defer db.Close()

    r := gin.Default()

    r.POST("/admin/login", func(c *gin.Context) {
        handleAdminLogin(c, db)
    })

    r.GET("/admin/loadusers", func(c *gin.Context) {
        loadUsers(c, db)
    })

    r.POST("/user/login", func(c *gin.Context) {
        handleUserLogin(c, db)
    })

    r.POST("/user/register", func(c *gin.Context) {
        handleUserRegistration(c, db)
    })

    r.GET("/user/info", func(c *gin.Context) {
        getUserInfo(c, db)
    })

    r.PUT("/user/update", func(c *gin.Context) {
        updateUserInfo(c, db)
    })

    r.GET("/parking/spots", func(c *gin.Context) {
        getParkingSpots(c, db)
    })

    r.PUT("/user/bookspot", func(c *gin.Context) {
        bookParkingSpot(c, db)
    })

    r.GET("/user/billing_history", func(c *gin.Context) {
        loadBillingHistory(c, db)
    })

    r.GET("/user/wallet", func(c *gin.Context) {
        loadWallet(c, db)
    })

    r.PUT("/user/recharge", func(c *gin.Context) {
        rechargeWallet(c, db)
    })

    r.Run(":8689")
}

func nullStringToString(ns sql.NullString) string {
    if ns.Valid {
        return ns.String
    }
    return ""
}

func handleAdminLogin(c *gin.Context, db *sql.DB) {
    var loginReq LoginRequest
    if err := c.ShouldBindJSON(&loginReq); err != nil {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid request"})
        return
    }
    log.Printf("Admin login attempt for username: %s", loginReq.Username)

    var storedUsername, storedPassword string
    query := "SELECT username, password FROM admin WHERE username = ?"
    err := db.QueryRow(query, loginReq.Username).Scan(&storedUsername, &storedPassword)
    if err != nil {
        if err == sql.ErrNoRows {
            c.JSON(http.StatusUnauthorized, gin.H{"status": "Unauthorized"})
            return
        }
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    if err := bcrypt.CompareHashAndPassword([]byte(storedPassword), []byte(loginReq.Password)); err != nil {
        c.JSON(http.StatusUnauthorized, gin.H{"status": "Unauthorized"})
        return
    }
    c.JSON(http.StatusOK, gin.H{"status": "Login successful"})
}

func loadUsers(c *gin.Context, db *sql.DB) {
    rows, err := db.Query("SELECT username, password, registration_date, car_plate, phone, email, avatar FROM users")
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }
    defer rows.Close()

    var users []UserInfo
    for rows.Next() {
        var user UserInfo
        if err := rows.Scan(&user.Username,
            &user.Password,
            &user.RegistrationDate,
            &user.CarPlate,
            &user.Phone,
            &user.Email,
            &user.Avatar);
        err != nil {
            c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
            return
        }
        user.UsernameStr = nullStringToString(user.Username)
        user.CarPlateStr = nullStringToString(user.CarPlate)
        user.EmailStr = nullStringToString(user.Email)
        user.AvatarStr = nullStringToString(user.Avatar)

        users = append(users, user)
    }

    if err := rows.Err(); err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    c.JSON(http.StatusOK, gin.H{"status": "success", "data": users})
}

func handleUserLogin(c *gin.Context, db *sql.DB) {
    var userLoginReq UserLoginRequest
    if err := c.ShouldBindJSON(&userLoginReq); err != nil {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid request"})
        return
    }
    log.Printf("User login attempt for phone: %s", userLoginReq.Phone)

    var storedPhone, storedPassword string
    query := "SELECT phone, password FROM users WHERE phone = ?"
    err := db.QueryRow(query, userLoginReq.Phone).Scan(&storedPhone, &storedPassword)
    if err != nil {
        if err == sql.ErrNoRows {
            c.JSON(http.StatusUnauthorized, gin.H{"status": "Unauthorized"})
            return
        }
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    if err := bcrypt.CompareHashAndPassword([]byte(storedPassword), []byte(userLoginReq.Password)); err != nil {
        c.JSON(http.StatusUnauthorized, gin.H{"status": "Unauthorized"})
        return
    }
    c.JSON(http.StatusOK, gin.H{"status": "Login successful"})
}

func handleUserRegistration(c *gin.Context, db *sql.DB) {
    var regReq UserRegisterRequest
    if err := c.ShouldBindJSON(&regReq); err != nil {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid request"})
        return
    }
    log.Printf("There is a user registration request: %s", regReq.Phone)

    phoneRegex := `^(13[0-9]|14[01456879]|15[0-35-9]|16[2567]|17[0-8]|18[0-9]|19[0-35-9])\d{8}$`
    matched, err := regexp.MatchString(phoneRegex, regReq.Phone)
    if err != nil || !matched {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid phone number format"})
        return
    }

    if len(regReq.Password) < 8 {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Password must be at least 8 characters long"})
        return
    }

    var existingPhone string
    query := "SELECT phone FROM users WHERE phone = ?"
    err = db.QueryRow(query, regReq.Phone).Scan(&existingPhone)
    if err != nil && err != sql.ErrNoRows {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }
    if existingPhone != "" {
        c.JSON(http.StatusBadRequest, gin.H{"status": "Phone number already registered"})
        return
    }

    hashedPassword, err := bcrypt.GenerateFromPassword([]byte(regReq.Password), bcrypt.DefaultCost)
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    insertQuery := "INSERT INTO users (phone, password, registration_date) VALUES (?, ?, ?)"
    result, err := db.Exec(insertQuery, regReq.Phone, hashedPassword, regReq.RegistrationDate)
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    userID, err := result.LastInsertId()
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    initWalletQuery := "INSERT INTO wallets (user_id, balance, last_recharge_date, auto_payment) VALUES (?, 0.00, NULL, 0)"
    _, err = db.Exec(initWalletQuery, userID)
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    c.JSON(http.StatusOK, gin.H{"status": "Registration successful"})
}

func getUserInfo(c *gin.Context, db *sql.DB) {
    phone := c.Query("phone")

    if phone == "" {
        c.JSON(http.StatusBadRequest, gin.H{"status": "Phone number is required"})
        return
    }

    var userInfo UserInfo
    query := "SELECT username, phone, email, car_plate, avatar FROM users WHERE phone = ?"
    err := db.QueryRow(query, phone).Scan(&userInfo.Username, &userInfo.Phone, &userInfo.Email, &userInfo.CarPlate, &userInfo.Avatar)
    if err != nil {
        if err == sql.ErrNoRows {
            log.Printf("User not found for phone: %s", phone)
            c.JSON(http.StatusNotFound, gin.H{"status": "User not found"})
            return
        }
        log.Printf("Database error: %v", err)
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    response := gin.H{
        "status": "success",
        "data": gin.H{
            "username":  nullStringToString(userInfo.Username),
            "phone":     userInfo.Phone,
            "email":     nullStringToString(userInfo.Email),
            "car_plate": nullStringToString(userInfo.CarPlate),
            "avatar":    nullStringToString(userInfo.Avatar),
        },
    }

    c.JSON(http.StatusOK, response)
}

func updateUserInfo(c *gin.Context, db *sql.DB) {
    var updateReq UpdateUserInfoRequest
    if err := c.ShouldBindJSON(&updateReq); err != nil {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid request"})
        return
    }

    query := "UPDATE users SET username = ?, email = ?, car_plate = ?, avatar = ? WHERE phone = ?"
    _, err := db.Exec(query, updateReq.Username, updateReq.Email, updateReq.CarPlate, updateReq.Avatar, updateReq.Phone)
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    c.JSON(http.StatusOK, gin.H{"status": "Update successful"})
}

func getParkingSpots(c *gin.Context, db *sql.DB) {
    rows, err := db.Query("SELECT spot_id, spot_number, is_available FROM parking_spots")
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }
    defer rows.Close()

    var spots []ParkingSpot
    for rows.Next() {
        var spot ParkingSpot
        if err := rows.Scan(&spot.SpotID, &spot.SpotNumber, &spot.IsAvailable); err != nil {
            c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
            return
        }
        spots = append(spots, spot)
    }

    if err := rows.Err(); err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    c.JSON(http.StatusOK, gin.H{"status": "success", "data": spots})
}

func bookParkingSpot(c *gin.Context, db *sql.DB) {
    var bookReq BookSpotRequest
    if err := c.ShouldBindJSON(&bookReq); err != nil {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid request"})
        return
    }

    var userID int
    getUserIDQuery := "SELECT user_id FROM users WHERE phone = ?"
    if err := db.QueryRow(getUserIDQuery, bookReq.Phone).Scan(&userID); err != nil {
        if err == sql.ErrNoRows {
            c.JSON(http.StatusNotFound, gin.H{"status": "User not found"})
            return
        }
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    var existingSpotID int
    checkUserQuery := "SELECT spot_number FROM parking_spots WHERE user_id = ?"
    if err := db.QueryRow(checkUserQuery, userID).Scan(&existingSpotID); err != nil && err != sql.ErrNoRows {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }
    if existingSpotID != 0 {
        c.JSON(http.StatusBadRequest, gin.H{"status": "User already booked a spot"})
        return
    }

    var isAvailable bool
    checkSpotQuery := "SELECT is_available FROM parking_spots WHERE spot_number = ?"
    if err := db.QueryRow(checkSpotQuery, bookReq.SpotNumber).Scan(&isAvailable); err != nil {
        if err == sql.ErrNoRows {
            c.JSON(http.StatusNotFound, gin.H{"status": "Spot not found"})
            return
        }
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }
    if !isAvailable {
        c.JSON(http.StatusBadRequest, gin.H{"status": "Spot is already booked"})
        return
    }

    updateQuery := "UPDATE parking_spots SET is_available = false, user_id = ? WHERE spot_number = ?"
    if _, err := db.Exec(updateQuery, userID, bookReq.SpotNumber); err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    c.JSON(http.StatusOK, gin.H{"status": "Booking successful"})
}

func loadBillingHistory(c *gin.Context, db *sql.DB) {
    phone := c.Query("phone")
    if phone == "" {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Phone number is required"})
        return
    }

    var userID int
    getUserIDQuery := "SELECT user_id FROM users WHERE phone = ?"
    if err := db.QueryRow(getUserIDQuery, phone).Scan(&userID); err != nil {
        if err == sql.ErrNoRows {
            c.JSON(http.StatusNotFound, gin.H{"status": "User not found"})
            return
        }
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    rows, err := db.Query("SELECT bill_id, user_id, order_id, payment_date, amount FROM billing_history WHERE user_id = ?", userID)
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }
    defer rows.Close()

    var history []BillingHistory
    for rows.Next() {
        var record BillingHistory
        if err := rows.Scan(&record.BillID, &record.UserID, &record.OrderID, &record.PaymentDate, &record.Amount); err != nil {
            c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
            return
        }
        history = append(history, record)
    }

    if err := rows.Err(); err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    c.JSON(http.StatusOK, gin.H{"status": "success", "data": history})
}

func loadWallet(c *gin.Context, db *sql.DB) {
    phone := c.Query("phone")
    if phone == "" {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Phone number is required"})
        return
    }

    var wallet WalletInfo
    query := `
        SELECT wallet_id, user_id, balance, last_recharge_date, auto_payment
        FROM wallets
        WHERE user_id = (SELECT user_id FROM users WHERE phone = ?)
    `
    if err := db.QueryRow(query, phone).Scan(
        &wallet.WalletID,
        &wallet.UserID,
        &wallet.Balance,
        &wallet.LastRechargeDate,
        &wallet.AutoPayment); err != nil {
        if err == sql.ErrNoRows {
            c.JSON(http.StatusNotFound, gin.H{"status": "User not found"})
            return
        }
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    response := gin.H{
        "status": "success",
        "data": gin.H{
            "wallet_id":          wallet.WalletID,
            "user_id":            wallet.UserID,
            "balance":            wallet.Balance,
            "late_recharge_date": nullStringToString(wallet.LastRechargeDate),
            "auto_payment":       wallet.AutoPayment,
        },
    }
    
    c.JSON(http.StatusOK, response)
}

func rechargeWallet(c *gin.Context, db *sql.DB) {
    var req RechargeRequest
    if err := c.ShouldBindJSON(&req); err != nil {
        c.JSON(http.StatusBadRequest, gin.H{"error": "Invalid request"})
        return
    }

    query := `
        UPDATE wallets
        SET balance = balance + ?, last_recharge_date = ?
        WHERE user_id = (SELECT user_id FROM users WHERE phone = ?)
    `
    result, err := db.Exec(query, req.Amount, req.LastRechargeDate, req.Phone)
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    rowsAffected, err := result.RowsAffected()
    if err != nil {
        c.JSON(http.StatusInternalServerError, gin.H{"status": "Internal Server Error"})
        return
    }

    if rowsAffected == 0 {
        c.JSON(http.StatusNotFound, gin.H{"status": "User not found"})
        return
    }

    c.JSON(http.StatusOK, gin.H{"status": "Recharge successful"})
}
