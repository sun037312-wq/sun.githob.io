<!DOCTYPE html>
<html lang="th" class="scroll-smooth">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SUN Inventory - ระบบบริหารจัดการสต็อกสินค้า</title>
    <!-- Tailwind CSS CDN -->
    <script src="https://cdn.tailwindcss.com"></script>
    <!-- Font Awesome Icons -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    <!-- Google Fonts -->
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Sarabun:ital,wght@0,300;0,400;0,500;0,600;0,700;1,300;1,400&display=swap" rel="stylesheet">
    
    <script>
        tailwind.config = {
            darkMode: 'class',
            theme: {
                extend: {
                    fontFamily: {
                        sarabun: ['Sarabun', 'sans-serif'],
                    },
                    animation: {
                        'gradient-x': 'gradient-x 15s ease infinite',
                        'pulse-slow': 'pulse 3s cubic-bezier(0.4, 0, 0.6, 1) infinite',
                    },
                    keyframes: {
                        'gradient-x': {
                            '0%, 100%': { 'background-position': '0% 50%' },
                            '50%': { 'background-position': '100% 50%' },
                        }
                    }
                }
            }
        }
    </script>
    <style>
        body {
            font-family: 'Sarabun', sans-serif;
        }
        .glass {
            background: rgba(255, 255, 255, 0.15);
            backdrop-filter: blur(12px);
            -webkit-backdrop-filter: blur(12px);
            border: 1px solid rgba(255, 255, 255, 0.2);
        }
        .dark .glass {
            background: rgba(15, 23, 42, 0.45);
            backdrop-filter: blur(12px);
            -webkit-backdrop-filter: blur(12px);
            border: 1px solid rgba(255, 255, 255, 0.05);
        }
        /* ซ่อน Scrollbar ของบราวเซอร์เพื่อความสวยงาม */
        ::-webkit-scrollbar {
            width: 8px;
        }
        ::-webkit-scrollbar-track {
            background: rgba(0,0,0,0.05);
        }
        ::-webkit-scrollbar-thumb {
            background: rgba(156, 163, 175, 0.5);
            border-radius: 4px;
        }
        ::-webkit-scrollbar-thumb:hover {
            background: rgba(156, 163, 175, 0.7);
        }
    </style>
</head>
<body class="bg-slate-100 text-slate-800 dark:bg-slate-900 dark:text-slate-100 min-h-screen flex flex-col transition-colors duration-300">

    <!-- การแจ้งเตือนที่กำหนดเอง (Custom Alert Toast) -->
    <div id="toast" class="fixed top-5 right-5 z-50 transform translate-x-full transition-all duration-300 ease-out max-w-sm w-full bg-white dark:bg-slate-800 rounded-lg shadow-xl p-4 border-l-4 border-blue-500 flex items-start space-x-3 hidden">
        <div id="toast-icon-box" class="text-blue-500 text-xl">
            <i class="fa-solid fa-circle-info"></i>
        </div>
        <div class="flex-1">
            <h4 id="toast-title" class="font-bold text-sm text-slate-900 dark:text-white">แจ้งเตือน</h4>
            <p id="toast-message" class="text-xs text-slate-600 dark:text-slate-300 mt-1">ข้อความระบบ...</p>
        </div>
        <button onclick="closeToast()" class="text-slate-400 hover:text-slate-600 dark:hover:text-slate-200">
            <i class="fa-solid fa-xmark"></i>
        </button>
    </div>

    <!-- ================== 1. หน้าต่างล็อกอิน (LOGIN SCREEN) ================== -->
    <div id="login-container" class="fixed inset-0 z-40 flex items-center justify-center p-4 bg-gradient-to-br from-indigo-500 via-purple-500 to-pink-500 bg-[length:400%_400%] animate-gradient-x">
        <!-- เอฟเฟกต์วงกลมพื้นหลังตกแต่ง -->
        <div class="absolute w-72 h-72 bg-white/20 rounded-full blur-3xl -top-10 -left-10 animate-pulse-slow"></div>
        <div class="absolute w-96 h-96 bg-pink-500/20 rounded-full blur-3xl -bottom-20 -right-20 animate-pulse-slow"></div>

        <!-- การ์ดล็อกอิน -->
        <div class="glass w-full max-w-md rounded-2xl shadow-2xl overflow-hidden p-8 text-white relative z-10">
            <!-- หัวข้อหน้าต่างล็อกอิน -->
            <div class="text-center mb-8">
                <div class="inline-flex items-center justify-center w-16 h-16 rounded-full bg-white/10 backdrop-blur-md mb-4 border border-white/20">
                    <i class="fa-solid fa-boxes-stacked text-yellow-300 text-3xl"></i>
                </div>
                <h1 class="text-3xl font-extrabold tracking-wide mb-2 drop-shadow">SUN Inventory</h1>
                <p class="text-white/80 text-sm">ระบบบริหารจัดการและติดตามสต็อกสินค้าจำลอง</p>
            </div>

            <!-- ฟอร์มกรอกข้อมูล -->
            <form id="login-form" onsubmit="handleLogin(event)" class="space-y-6">
                <!-- อีเมล/ชื่อผู้ใช้ -->
                <div>
                    <label class="block text-xs font-semibold uppercase tracking-wider mb-2 text-white/90">ชื่อผู้ใช้งาน</label>
                    <div class="relative">
                        <span class="absolute inset-y-0 left-0 flex items-center pl-3 text-white/60">
                            <i class="fa-regular fa-user"></i>
                        </span>
                        <input type="text" id="username" required
                            class="w-full pl-10 pr-4 py-3 bg-white/10 focus:bg-white/20 border border-white/10 focus:border-white/40 rounded-xl outline-none transition-all placeholder-white/40 text-white text-sm"
                            placeholder="กรอกชื่อผู้ใช้งาน (admin)">
                    </div>
                </div>

                <!-- รหัสผ่าน -->
                <div>
                    <label class="block text-xs font-semibold uppercase tracking-wider mb-2 text-white/90">รหัสผ่าน</label>
                    <div class="relative">
                        <span class="absolute inset-y-0 left-0 flex items-center pl-3 text-white/60">
                            <i class="fa-solid fa-lock"></i>
                        </span>
                        <input type="password" id="password" required
                            class="w-full pl-10 pr-12 py-3 bg-white/10 focus:bg-white/20 border border-white/10 focus:border-white/40 rounded-xl outline-none transition-all placeholder-white/40 text-white text-sm"
                            placeholder="กรอกรหัสผ่าน (123456)">
                        <button type="button" onclick="togglePasswordVisibility()" class="absolute inset-y-0 right-0 flex items-center pr-3 text-white/60 hover:text-white">
                            <i id="password-toggle-icon" class="fa-regular fa-eye"></i>
                        </button>
                    </div>
                </div>

                <!-- ตัวเลือกเพิ่มเติม -->
                <div class="flex items-center justify-between text-xs text-white/80">
                    <label class="flex items-center space-x-2 cursor-pointer">
                        <input type="checkbox" class="rounded bg-white/10 border-white/20 focus:ring-0">
                        <span>จดจำฉันไว้</span>
                    </label>
                    <a href="#" onclick="showForgotPasswordModal(event)" class="hover:underline hover:text-white">ลืมรหัสผ่าน?</a>
                </div>

                <!-- ปุ่มส่งฟอร์ม -->
                <button type="submit"
                    class="w-full py-3 bg-white text-indigo-600 font-bold rounded-xl shadow-lg hover:bg-slate-100 hover:shadow-xl active:scale-[0.98] transition-all duration-150">
                    เข้าสู่ระบบ <i class="fa-solid fa-arrow-right ml-1"></i>
                </button>

                <!-- ปุ่มเข้าสู่ระบบด่วน / เกสท์ -->
                <div class="relative flex py-2 items-center">
                    <div class="flex-grow border-t border-white/20"></div>
                    <span class="flex-shrink mx-4 text-xs text-white/60">หรือ</span>
                    <div class="flex-grow border-t border-white/20"></div>
                </div>

                <button type="button" onclick="loginAsGuest()"
                    class="w-full py-2.5 bg-white/10 hover:bg-white/20 border border-white/20 text-white font-medium rounded-xl text-sm active:scale-[0.98] transition-all">
                    <i class="fa-solid fa-user-secret mr-1"></i> เข้าใช้ในฐานะบุคคลทั่วไป
                </button>
            </form>

            <!-- ข้อมูลบัญชีผู้ใช้ทดสอบ -->
            <div class="mt-8 pt-4 border-t border-white/10 text-center text-xs text-white/70">
                <p><i class="fa-solid fa-circle-info mr-1"></i> <strong>ข้อมูลเข้าสู่ระบบแบบทดสอบ</strong></p>
                <p class="mt-1">ผู้ใช้: <span class="underline">admin</span> | รหัสผ่าน: <span class="underline">123456</span></p>
            </div>
        </div>
    </div>

    <!-- หน้าต่างลืมรหัสผ่าน (Modal) -->
    <div id="forgot-password-modal" class="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/50 backdrop-blur-sm hidden">
        <div class="bg-white dark:bg-slate-800 rounded-2xl max-w-sm w-full p-6 shadow-2xl text-slate-800 dark:text-slate-100">
            <h3 class="text-lg font-bold mb-2">กู้คืนรหัสผ่าน</h3>
            <p class="text-sm text-slate-500 dark:text-slate-400 mb-4">ระบบจะส่งลิงก์สำหรับเปลี่ยนรหัสผ่านใหม่ไปยังที่อยู่อีเมลของคุณ</p>
            <input type="email" placeholder="อีเมลของคุณ" id="reset-email" class="w-full px-4 py-2 border dark:border-slate-700 rounded-xl bg-slate-50 dark:bg-slate-900 outline-none mb-4 focus:ring-2 focus:ring-blue-500 text-sm">
            <div class="flex justify-end space-x-2">
                <button onclick="closeForgotPasswordModal()" class="px-4 py-2 text-sm font-semibold rounded-lg text-slate-500 hover:bg-slate-100 dark:hover:bg-slate-700">ยกเลิก</button>
                <button onclick="handleResetPassword()" class="px-4 py-2 text-sm font-semibold rounded-lg bg-indigo-600 text-white hover:bg-indigo-700">ยืนยันส่งข้อมูล</button>
            </div>
        </div>
    </div>


    <!-- ================== 2. ระบบแดชบอร์ดจัดการสต็อกสินค้า (MAIN DASHBOARD) ================== -->
    <div id="dashboard-container" class="hidden flex-1 flex flex-col">
        
        <!-- แถบนำทางด้านบน (Navbar) -->
        <nav class="bg-white/80 dark:bg-slate-900/80 backdrop-blur-md sticky top-0 z-30 border-b border-slate-200 dark:border-slate-800 transition-colors">
            <div class="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
                <div class="flex justify-between h-16">
                    <div class="flex items-center">
                        <div class="flex-shrink-0 flex items-center space-x-2">
                            <span class="w-10 h-10 rounded-xl bg-gradient-to-tr from-amber-400 to-rose-500 flex items-center justify-center shadow-md">
                                <i class="fa-solid fa-boxes-stacked text-white text-xl"></i>
                            </span>
                            <span class="font-bold text-xl tracking-wider text-slate-900 dark:text-white">SUN<span class="text-amber-500">.inventory</span></span>
                        </div>
                        <div class="hidden md:ml-6 md:flex md:space-x-4">
                            <a href="#dashboard-view" onclick="switchTab('dashboard')" class="nav-tab-btn px-3 py-2 rounded-md text-sm font-medium text-amber-500 border-b-2 border-amber-500">แผงควบคุมหลัก</a>
                            <a href="#stock-view" onclick="switchTab('stock')" class="nav-tab-btn px-3 py-2 rounded-md text-sm font-medium text-slate-500 hover:text-slate-900 dark:hover:text-white">ตารางสินค้า</a>
                        </div>
                    </div>

                    <!-- ปุ่มควบคุมด้านขวา -->
                    <div class="flex items-center space-x-3">
                        <!-- ปุ่มเปิด/ปิด โหมดมืด -->
                        <button onclick="toggleDarkMode()" class="p-2.5 rounded-xl bg-slate-100 dark:bg-slate-800 text-slate-600 dark:text-slate-300 hover:bg-slate-200 dark:hover:bg-slate-700 transition-colors" title="เปลี่ยนโหมดสี">
                            <i id="theme-icon" class="fa-regular fa-moon text-lg"></i>
                        </button>

                        <!-- เมนูโปรไฟล์ / ลงชื่อออก -->
                        <div class="relative group">
                            <button class="flex items-center space-x-2 p-1.5 rounded-full hover:bg-slate-100 dark:hover:bg-slate-800 transition-colors">
                                <img id="user-avatar" class="h-8 w-8 rounded-full border-2 border-amber-400" src="https://images.unsplash.com/photo-1535713875002-d1d0cf377fde?auto=format&fit=crop&w=150&q=80" alt="อวาตาร์">
                                <span id="user-display-name" class="hidden sm:inline text-sm font-medium pr-2 text-slate-700 dark:text-slate-300">Admin</span>
                            </button>
                            <!-- เมนูดรอปดาวน์ -->
                            <div class="absolute right-0 mt-2 w-48 bg-white dark:bg-slate-800 rounded-xl shadow-lg border border-slate-200 dark:border-slate-700 py-1 hidden group-hover:block">
                                <div class="px-4 py-2 border-b border-slate-100 dark:border-slate-700">
                                    <p class="text-xs text-slate-400">เข้าใช้งานในชื่อ</p>
                                    <p id="user-dropdown-name" class="text-sm font-semibold truncate text-slate-800 dark:text-slate-200">Admin User</p>
                                </div>
                                <button onclick="handleLogout()" class="w-full text-left px-4 py-2.5 text-sm text-red-500 hover:bg-slate-50 dark:hover:bg-slate-700/50 flex items-center space-x-2">
                                    <i class="fa-solid fa-arrow-right-from-bracket"></i>
                                    <span>ออกจากระบบ</span>
                                </button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </nav>

        <!-- พื้นที่เนื้อหาหลัก (Main Content Area) -->
        <main class="flex-grow max-w-7xl w-full mx-auto px-4 sm:px-6 lg:px-8 py-8 space-y-8">
            
            <!-- ส่วนที่ 1: ต้อนรับผู้ใช้ (Welcome Hero Banner) -->
            <section class="relative rounded-3xl overflow-hidden shadow-xl bg-gradient-to-r from-slate-900 to-indigo-900 text-white p-6 sm:p-8">
                <!-- พื้นหลังลายกริด -->
                <div class="absolute inset-0 opacity-10 pointer-events-none">
                    <svg class="w-full h-full" xmlns="http://www.w3.org/2000/svg" width="100%" height="100%">
                        <rect width="100%" height="100%" fill="none" stroke="currentColor" stroke-width="1" />
                    </svg>
                </div>

                <div class="relative z-10 flex flex-col md:flex-row items-center justify-between gap-4">
                    <div class="space-y-2 max-w-xl text-center md:text-left">
                        <span class="px-3 py-1 bg-amber-500/20 text-amber-300 border border-amber-500/30 rounded-full text-xs font-bold uppercase tracking-wider">ระบบสินค้าคงคลัง</span>
                        <h2 class="text-2xl sm:text-4xl font-extrabold leading-tight">สวัสดีคุณ <span id="hero-username-span" class="text-amber-400">Admin</span></h2>
                        <p class="text-slate-300 text-xs sm:text-sm">
                            ที่นี่คือศูนย์จัดการคลังสินค้าอัจฉริยะ คุณสามารถเช็คระดับคงเหลือ ตรวจสอบผลกำไรคาดการณ์ และทำการปรับสต็อก รับเข้า/จำหน่ายออก ได้อย่างสมบูรณ์แบบในที่เดียว
                        </p>
                    </div>
                    <!-- ปุ่มด่วน -->
                    <div class="flex flex-wrap gap-2">
                        <button onclick="openAddProductModal()" class="px-5 py-2.5 bg-amber-500 hover:bg-amber-600 font-bold text-sm rounded-xl transition-all shadow-lg active:scale-95 flex items-center gap-1">
                            <i class="fa-solid fa-plus"></i> เพิ่มสินค้าใหม่
                        </button>
                    </div>
                </div>
            </section>

            <!-- แผงควบคุมสถิติ (Overview Statistics Cards) -->
            <section class="grid grid-cols-2 lg:grid-cols-4 gap-4">
                <!-- รวมประเภทสินค้า -->
                <div class="bg-white dark:bg-slate-800 rounded-2xl p-4 shadow-md border border-slate-100 dark:border-slate-700 flex items-center space-x-4">
                    <div class="p-3 bg-blue-100 dark:bg-blue-900/40 text-blue-600 dark:text-blue-400 rounded-xl text-2xl">
                        <i class="fa-solid fa-layer-group"></i>
                    </div>
                    <div>
                        <p class="text-xs text-slate-400 font-semibold">จำนวนประเภทสินค้า</p>
                        <h4 id="stat-total-types" class="text-xl sm:text-2xl font-black">0</h4>
                    </div>
                </div>
                <!-- จำนวนชิ้นรวมทั้งหมด -->
                <div class="bg-white dark:bg-slate-800 rounded-2xl p-4 shadow-md border border-slate-100 dark:border-slate-700 flex items-center space-x-4">
                    <div class="p-3 bg-amber-100 dark:bg-amber-900/40 text-amber-600 dark:text-amber-400 rounded-xl text-2xl">
                        <i class="fa-solid fa-boxes-stacked"></i>
                    </div>
                    <div>
                        <p class="text-xs text-slate-400 font-semibold">จำนวนสินค้าในคลัง</p>
                        <h4 id="stat-total-quantity" class="text-xl sm:text-2xl font-black">0 <span class="text-xs font-normal">ชิ้น</span></h4>
                    </div>
                </div>
                <!-- มูลค่าต้นทุนรวม -->
                <div class="bg-white dark:bg-slate-800 rounded-2xl p-4 shadow-md border border-slate-100 dark:border-slate-700 flex items-center space-x-4">
                    <div class="p-3 bg-emerald-100 dark:bg-emerald-900/40 text-emerald-600 dark:text-emerald-400 rounded-xl text-2xl">
                        <i class="fa-solid fa-hand-holding-dollar"></i>
                    </div>
                    <div>
                        <p class="text-xs text-slate-400 font-semibold">มูลค่าต้นทุนรวม</p>
                        <h4 id="stat-total-cost" class="text-xl sm:text-2xl font-black">฿0</h4>
                    </div>
                </div>
                <!-- สินค้าใกล้หมดสต็อก -->
                <div class="bg-white dark:bg-slate-800 rounded-2xl p-4 shadow-md border border-slate-100 dark:border-slate-700 flex items-center space-x-4">
                    <div class="p-3 bg-rose-100 dark:bg-rose-900/40 text-rose-600 dark:text-rose-400 rounded-xl text-2xl">
                        <i class="fa-solid fa-triangle-exclamation animate-bounce"></i>
                    </div>
                    <div>
                        <p class="text-xs text-slate-400 font-semibold">สต็อกเหลือน้อย (&le;5)</p>
                        <h4 id="stat-low-stock" class="text-xl sm:text-2xl font-black text-rose-500">0</h4>
                    </div>
                </div>
            </section>

            <!-- TAB 1: Dashboard View -->
            <div id="tab-dashboard" class="space-y-6">
                <div class="grid grid-cols-1 lg:grid-cols-3 gap-6">
                    <!-- ส่วนแสดงประวัติบันทึกการปรับเปลี่ยนสต็อกสินค้าล่าสุด -->
                    <div class="lg:col-span-2 bg-white dark:bg-slate-800 rounded-2xl p-6 shadow-md border border-slate-100 dark:border-slate-700 flex flex-col min-h-[400px]">
                        <div class="flex justify-between items-center mb-4 pb-2 border-b dark:border-slate-700">
                            <h4 class="font-bold text-base flex items-center gap-2">
                                <i class="fa-solid fa-clock-rotate-left text-indigo-500"></i> ประวัติการอัปเดตสต็อกล่าสุด
                            </h4>
                            <button onclick="clearHistory()" class="text-xs text-slate-400 hover:text-red-500"><i class="fa-regular fa-trash-can"></i> ล้างประวัติ</button>
                        </div>
                        
                        <!-- รายการประวัติแบบเลื่อนได้ -->
                        <div id="history-list" class="flex-grow overflow-y-auto space-y-2 max-h-[300px] pr-1">
                            <!-- จะนำเข้าประวัติด้วย JavaScript -->
                            <div class="text-center py-16 text-slate-400">
                                <i class="fa-solid fa-receipt text-3xl mb-2"></i>
                                <p class="text-xs">ยังไม่มีความเคลื่อนไหวในสต็อกขณะนี้</p>
                            </div>
                        </div>
                    </div>

                    <!-- มินิเกมแก้เบื่อสำหรับเด็กและเยาวชน (สะสมคะแนนเพิ่มพลังใจ) -->
                    <div class="bg-white dark:bg-slate-800 rounded-2xl p-6 shadow-md border border-slate-100 dark:border-slate-700 flex flex-col">
                        <div class="flex justify-between items-center mb-4 pb-2 border-b dark:border-slate-700">
                            <h4 class="font-bold text-base flex items-center gap-2">
                                <i class="fa-solid fa-gamepad text-purple-500"></i> เกมจัดเรียงกล่องด่วน!
                            </h4>
                            <span class="px-2 py-0.5 bg-purple-100 dark:bg-purple-900/30 text-purple-600 text-xs font-semibold rounded">แก้เครียด</span>
                        </div>
                        <div class="flex-grow flex flex-col items-center justify-center text-center space-y-4">
                            <p class="text-xs text-slate-500">คลิกจัดสินค้าจัดเรียงเข้าชั้นวาง เพื่อรับคะแนนผู้จัดการยอดเยี่ยม!</p>
                            
                            <div class="relative w-32 h-32 flex items-center justify-center bg-slate-50 dark:bg-slate-900 rounded-2xl border-2 border-dashed border-slate-200 dark:border-slate-700">
                                <i id="game-box-icon" class="fa-solid fa-box text-amber-500 text-5xl transition-all duration-150"></i>
                            </div>

                            <div>
                                <h5 class="text-xs text-slate-400 font-bold uppercase tracking-wider">คะแนนความเร็วสะสม</h5>
                                <p id="game-score" class="text-3xl font-black text-indigo-500 dark:text-indigo-400">0</p>
                            </div>

                            <button onclick="playMiniGame()" class="w-full py-2.5 bg-indigo-600 hover:bg-indigo-700 text-white text-sm font-bold rounded-xl transition-all shadow-md active:scale-95">
                                <i class="fa-solid fa-hand-pointer mr-1 animate-pulse"></i> จัดเรียงสินค้า 1 กล่อง!
                            </button>
                        </div>
                    </div>
                </div>
            </div>

            <!-- TAB 2: ตารางข้อมูลสินค้าและค้นหา -->
            <div id="tab-stock" class="space-y-4 hidden">
                <!-- แถบค้นหาและการกรอง -->
                <div class="flex flex-col sm:flex-row gap-3 justify-between items-center bg-white dark:bg-slate-800 p-4 rounded-2xl shadow-sm border border-slate-100 dark:border-slate-700">
                    <div class="relative w-full sm:max-w-xs">
                        <span class="absolute inset-y-0 left-0 flex items-center pl-3 text-slate-400">
                            <i class="fa-solid fa-magnifying-glass text-sm"></i>
                        </span>
                        <input type="text" id="search-input" oninput="filterProducts()" placeholder="ค้นหาสินค้าด้วยชื่อ..."
                            class="w-full pl-9 pr-4 py-2 text-sm border dark:border-slate-700 rounded-xl bg-slate-50 dark:bg-slate-900 outline-none focus:ring-2 focus:ring-amber-500">
                    </div>

                    <!-- ฟิลเตอร์เลือกประเภท -->
                    <div class="flex gap-2 w-full sm:w-auto">
                        <select id="filter-category" onchange="filterProducts()" class="px-3 py-2 text-sm border dark:border-slate-700 rounded-xl bg-slate-50 dark:bg-slate-900 outline-none focus:ring-2 focus:ring-amber-500 flex-1 sm:flex-none">
                            <option value="all">ทุกหมวดหมู่</option>
                            <option value="เครื่องเขียน">เครื่องเขียน</option>
                            <option value="เทคโนโลยี">เทคโนโลยี</option>
                            <option value="อุปกรณ์กีฬา">อุปกรณ์กีฬา</option>
                            <option value="ของกินเล่น">ของกินเล่น</option>
                            <option value="อื่นๆ">อื่นๆ</option>
                        </select>
                    </div>
                </div>

                <!-- ตารางสินค้า Responsive -->
                <div class="bg-white dark:bg-slate-800 rounded-2xl overflow-hidden shadow-md border border-slate-100 dark:border-slate-700">
                    <div class="overflow-x-auto">
                        <table class="w-full text-left border-collapse">
                            <thead>
                                <tr class="bg-slate-50 dark:bg-slate-900/50 text-slate-400 text-xs font-bold uppercase tracking-wider border-b border-slate-100 dark:border-slate-800">
                                    <th class="py-3.5 px-4 sm:px-6">ชื่อสินค้า</th>
                                    <th class="py-3.5 px-4">หมวดหมู่</th>
                                    <th class="py-3.5 px-4 text-center">คงเหลือ (สต็อก)</th>
                                    <th class="py-3.5 px-4 text-right">ต้นทุน/หน่วย</th>
                                    <th class="py-3.5 px-4 text-right">ราคาจำหน่าย</th>
                                    <th class="py-3.5 px-4 text-right">กำไรคาดการณ์</th>
                                    <th class="py-3.5 px-4 text-center">การจัดการ</th>
                                </tr>
                            </thead>
                            <tbody id="product-table-body" class="divide-y divide-slate-100 dark:divide-slate-800 text-sm">
                                <!-- สินค้าในคลังจะถูกแสดงผลด้วย JavaScript -->
                            </tbody>
                        </table>
                    </div>
                    <!-- ข้อความเมื่อไม่มีข้อมูลสินค้าเลย -->
                    <div id="no-products" class="text-center py-16 text-slate-400 hidden">
                        <i class="fa-solid fa-box-open text-4xl mb-2"></i>
                        <p class="text-sm">ไม่พบสินค้าในรายการที่ค้นหา กรุณาเพิ่มสินค้าใหม่</p>
                    </div>
                </div>
            </div>

        </main>

        <!-- แถบด้านล่าง (Footer) -->
        <footer class="bg-white dark:bg-slate-950 border-t border-slate-200 dark:border-slate-800 transition-colors py-6 text-center text-xs text-slate-500 dark:text-slate-400">
            <p>© 2026 SUN Inventory - ระบบควบคุมสต็อกพรีเมียมปลอดภัยสำหรับผู้ใช้</p>
            <p class="mt-1">พัฒนาด้วยความรักและความรู้จำลองสำหรับระบบการบริหารสต็อกของเยาวชน</p>
        </footer>

    </div>

    <!-- ================== MODAL หน้าต่าง: เพิ่ม/แก้ไข สินค้า ================== -->
    <div id="product-modal" class="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/50 backdrop-blur-sm hidden">
        <div class="bg-white dark:bg-slate-800 rounded-2xl max-w-md w-full p-6 shadow-2xl text-slate-800 dark:text-slate-100 relative">
            <button onclick="closeProductModal()" class="absolute top-4 right-4 text-slate-400 hover:text-slate-600 dark:hover:text-slate-200 text-xl">
                <i class="fa-solid fa-xmark"></i>
            </button>
            
            <div class="mb-4">
                <h3 id="product-modal-title" class="text-lg font-bold">เพิ่มสินค้าใหม่เข้าสต็อก</h3>
                <p class="text-xs text-slate-400">กรอกข้อมูลรายละเอียดของสินค้าเพื่อบันทึกลงในฐานข้อมูลระบบ</p>
            </div>

            <form id="product-form" onsubmit="handleSaveProduct(event)" class="space-y-4">
                <input type="hidden" id="edit-product-id">
                
                <!-- ชื่อสินค้า -->
                <div>
                    <label class="block text-xs font-bold uppercase tracking-wider text-slate-400 mb-1">ชื่อสินค้า *</label>
                    <input type="text" id="p-name" required placeholder="เช่น สมุดโน้ตปกแข็งถนอมสายตา"
                        class="w-full px-4 py-2 text-sm border dark:border-slate-700 rounded-xl bg-slate-50 dark:bg-slate-900 outline-none focus:ring-2 focus:ring-amber-500">
                </div>

                <!-- หมวดหมู่ -->
                <div>
                    <label class="block text-xs font-bold uppercase tracking-wider text-slate-400 mb-1">หมวดหมู่สินค้า</label>
                    <select id="p-category" class="w-full px-4 py-2 text-sm border dark:border-slate-700 rounded-xl bg-slate-50 dark:bg-slate-900 outline-none focus:ring-2 focus:ring-amber-500">
                        <option value="เครื่องเขียน">เครื่องเขียน</option>
                        <option value="เทคโนโลยี">เทคโนโลยี</option>
                        <option value="อุปกรณ์กีฬา">อุปกรณ์กีฬา</option>
                        <option value="ของกินเล่น">ของกินเล่น</option>
                        <option value="อื่นๆ">อื่นๆ</option>
                    </select>
                </div>

                <div class="grid grid-cols-3 gap-3">
                    <!-- จำนวนสินค้าคงเหลือเริ่มต้น -->
                    <div>
                        <label class="block text-xs font-bold uppercase tracking-wider text-slate-400 mb-1">คงเหลือ *</label>
                        <input type="number" id="p-qty" required min="0" placeholder="0"
                            class="w-full px-4 py-2 text-sm border dark:border-slate-700 rounded-xl bg-slate-50 dark:bg-slate-900 outline-none focus:ring-2 focus:ring-amber-500">
                    </div>
                    <!-- ต้นทุนต่อชิ้น -->
                    <div>
                        <label class="block text-xs font-bold uppercase tracking-wider text-slate-400 mb-1">ต้นทุน (฿) *</label>
                        <input type="number" id="p-cost" required min="0" placeholder="0"
                            class="w-full px-4 py-2 text-sm border dark:border-slate-700 rounded-xl bg-slate-50 dark:bg-slate-900 outline-none focus:ring-2 focus:ring-amber-500">
                    </div>
                    <!-- ราคาตั้งขายต่อชิ้น -->
                    <div>
                        <label class="block text-xs font-bold uppercase tracking-wider text-slate-400 mb-1">ราคาขาย (฿) *</label>
                        <input type="number" id="p-price" required min="0" placeholder="0"
                            class="w-full px-4 py-2 text-sm border dark:border-slate-700 rounded-xl bg-slate-50 dark:bg-slate-900 outline-none focus:ring-2 focus:ring-amber-500">
                    </div>
                </div>

                <!-- การทำรายการเพิ่ม/ลบ สต็อกด่วนแบบทันใจกรณีแก้ไขสินค้า -->
                <div id="quick-stock-adjust-section" class="hidden pt-3 border-t dark:border-slate-700">
                    <label class="block text-xs font-bold uppercase tracking-wider text-slate-400 mb-2">ปรับยอดสต็อกด่วน</label>
                    <div class="flex items-center space-x-2">
                        <button type="button" onclick="adjustQuickStock(-1)" class="px-3 py-1.5 bg-rose-500/15 text-rose-500 text-xs font-bold rounded-lg hover:bg-rose-500/20">- ลด 1 ชิ้น</button>
                        <button type="button" onclick="adjustQuickStock(1)" class="px-3 py-1.5 bg-emerald-500/15 text-emerald-500 text-xs font-bold rounded-lg hover:bg-emerald-500/20">+ เพิ่ม 1 ชิ้น</button>
                        <span class="text-xs text-slate-400 italic">(เปลี่ยนตามจริงและบันทึกประวัติทันที)</span>
                    </div>
                </div>

                <div class="flex justify-end space-x-2 pt-2">
                    <button type="button" onclick="closeProductModal()" class="px-4 py-2 text-sm font-semibold rounded-xl text-slate-500 hover:bg-slate-100 dark:hover:bg-slate-700">ยกเลิก</button>
                    <button type="submit" class="px-5 py-2 text-sm font-semibold rounded-xl bg-indigo-600 hover:bg-indigo-700 text-white shadow-md">บันทึกข้อมูล</button>
                </div>
            </form>
        </div>
    </div>


    <!-- ================== 3. ระบบควบคุมแอปพลิเคชัน (JavaScript) ================== -->
    <script>
        // บัญชีผู้ใช้จำลองสำหรับล็อกอินเข้าใช้ระบบ
        const MOCK_USER = {
            username: 'admin',
            password: 'password'
        };

        // ข้อมูลหลัก: สินค้าและประวัติบันทึกในระบบจำลอง
        let products = [
            { id: 101, name: "สมุดบันทึกหน้าปกแมวเหมียวน่ารัก", category: "เครื่องเขียน", quantity: 24, cost: 25, price: 49 },
            { id: 102, name: "ปากกาเจลนำเข้าจากญี่ปุ่น (สีดำ 0.5)", category: "เครื่องเขียน", quantity: 15, cost: 12, price: 29 },
            { id: 103, name: "สายชาร์จโทรศัพท์ Fast Charge USB-C", category: "เทคโนโลยี", quantity: 4, cost: 75, price: 150 },
            { id: 104, name: "ลูกบาสเก็ตบอลมาตรฐานหนังเทียม", category: "อุปกรณ์กีฬา", quantity: 12, cost: 280, price: 450 },
            { id: 105, name: "มันฝรั่งทอดกรอบคัดพิเศษแผ่นหยัก", category: "ของกินเล่น", quantity: 45, cost: 14, price: 20 }
        ];

        let stockHistory = [
            { id: 1, pName: "สมุดบันทึกหน้าปกแมวเหมียวน่ารัก", action: "รับเข้า", quantity: 24, timestamp: "01/07/2026, 08:30" },
            { id: 2, pName: "สายชาร์จโทรศัพท์ Fast Charge USB-C", action: "จ่ายออก", quantity: 2, timestamp: "01/07/2026, 08:45" }
        ];

        let currentUser = null;
        let miniGameScore = 0;

        // เริ่มโปรแกรมเมื่อเว็บโหลดเสร็จ
        window.addEventListener('DOMContentLoaded', () => {
            // เช็คการเปลี่ยนธีม
            if (localStorage.getItem('theme') === 'dark' || (!('theme' in localStorage) && window.matchMedia('(prefers-color-scheme: dark)').matches)) {
                document.documentElement.classList.add('dark');
                updateThemeIcon(true);
            } else {
                document.documentElement.classList.remove('dark');
                updateThemeIcon(false);
            }

            // คำนวณยอดสรุปแรกเริ่ม
            updateOverviewStats();
            renderProductTable();
            renderHistory();
        });

        // ------------------ ระบบล็อกอิน ------------------
        
        function togglePasswordVisibility() {
            const passwordInput = document.getElementById('password');
            const icon = document.getElementById('password-toggle-icon');
            if (passwordInput.type === 'password') {
                passwordInput.type = 'text';
                icon.className = 'fa-regular fa-eye-slash';
            } else {
                passwordInput.type = 'password';
                icon.className = 'fa-regular fa-eye';
            }
        }

        function handleLogin(event) {
            event.preventDefault();
            const usernameInput = document.getElementById('username').value.trim();
            const passwordInput = document.getElementById('password').value;

            // ตรวจสอบ username และรหัสผ่านที่ยอมรับ
            if (usernameInput.toLowerCase() === 'admin' && (passwordInput === '123456' || passwordInput === 'password')) {
                loginSuccess('ผู้จัดการสต็อก (Administrator)');
            } else {
                showToast('เข้าสู่ระบบล้มเหลว', 'ชื่อผู้ใช้งานหรือรหัสผ่านไม่ถูกต้อง กรุณาลองด้วย admin / 123456', 'error');
            }
        }

        function loginAsGuest() {
            loginSuccess('บุคคลทั่วไป (Guest)');
        }

        function loginSuccess(roleName) {
            currentUser = roleName;
            const loginContainer = document.getElementById('login-container');
            const dashboardContainer = document.getElementById('dashboard-container');
            
            loginContainer.classList.add('opacity-0', 'transition-opacity', 'duration-500');
            setTimeout(() => {
                loginContainer.classList.add('hidden');
                dashboardContainer.classList.remove('hidden');
                
                document.getElementById('user-display-name').innerText = roleName === 'บุคคลทั่วไป (Guest)' ? 'Guest' : 'Admin';
                document.getElementById('user-dropdown-name').innerText = roleName;
                document.getElementById('hero-username-span').innerText = roleName === 'บุคคลทั่วไป (Guest)' ? 'คุณเกสท์' : 'ผู้ดูแลระบบ';
                
                if (roleName === 'บุคคลทั่วไป (Guest)') {
                    document.getElementById('user-avatar').src = 'https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=150&q=80';
                }

                showToast('ยินดีต้อนรับ', 'เข้าสู่ระบบบริหารจัดการสต็อกสำเร็จแล้ว', 'success');
            }, 500);
        }

        function handleLogout() {
            const loginContainer = document.getElementById('login-container');
            const dashboardContainer = document.getElementById('dashboard-container');
            
            document.getElementById('username').value = '';
            document.getElementById('password').value = '';

            dashboardContainer.classList.add('hidden');
            loginContainer.classList.remove('hidden');
            loginContainer.classList.remove('opacity-0');
            
            currentUser = null;
            showToast('ลงชื่อออกสำเร็จ', 'คุณออกจากระบบอย่างปลอดภัยแล้ว', 'info');
        }

        // หน้าต่างลืมรหัสผ่าน
        function showForgotPasswordModal(event) {
            event.preventDefault();
            document.getElementById('forgot-password-modal').classList.remove('hidden');
        }

        function closeForgotPasswordModal() {
            document.getElementById('forgot-password-modal').classList.add('hidden');
            document.getElementById('reset-email').value = '';
        }

        function handleResetPassword() {
            const email = document.getElementById('reset-email').value.trim();
            if (email === "") {
                showToast('ข้อมูลว่างเปล่า', 'กรุณากรอกที่อยู่อีเมลก่อนส่งระบบส่งข้อมูล', 'error');
                return;
            }
            closeForgotPasswordModal();
            showToast('ส่งลิงก์เรียบร้อย', 'ส่งคำแนะนำการรีเซ็ตรหัสผ่านจำลองไปที่อีเมลเรียบร้อย!', 'success');
        }

        // ------------------ เปลี่ยนโหมดมืด/โหมดสว่าง ------------------
        
        function toggleDarkMode() {
            if (document.documentElement.classList.contains('dark')) {
                document.documentElement.classList.remove('dark');
                localStorage.setItem('theme', 'light');
                updateThemeIcon(false);
                showToast('โหมดสว่าง', 'สลับหน้าจอเป็นโทนสีสว่างเพื่อความเหมาะสม', 'info');
            } else {
                document.documentElement.classList.add('dark');
                localStorage.setItem('theme', 'dark');
                updateThemeIcon(true);
                showToast('โหมดมืด', 'สลับหน้าจอเป็นโหมดถนอมสายตาเรียบร้อย', 'info');
            }
        }

        function updateThemeIcon(isDark) {
            const icon = document.getElementById('theme-icon');
            if (isDark) {
                icon.className = 'fa-regular fa-sun text-lg text-amber-400';
            } else {
                icon.className = 'fa-regular fa-moon text-lg text-slate-600';
            }
        }

        // ------------------ สลับแถบเมนู (Tabs Switcher) ------------------
        
        function switchTab(tabName) {
            const tabButtons = document.querySelectorAll('.nav-tab-btn');
            tabButtons.forEach(btn => {
                btn.className = 'nav-tab-btn px-3 py-2 rounded-md text-sm font-medium text-slate-500 hover:text-slate-900 dark:hover:text-white';
            });

            // ตกแต่งปุ่มที่ทำงานอยู่
            event.currentTarget.className = 'nav-tab-btn px-3 py-2 rounded-md text-sm font-medium text-amber-500 border-b-2 border-amber-500';

            const tabDashboard = document.getElementById('tab-dashboard');
            const tabStock = document.getElementById('tab-stock');

            if (tabName === 'dashboard') {
                tabDashboard.classList.remove('hidden');
                tabStock.classList.add('hidden');
            } else {
                tabDashboard.classList.add('hidden');
                tabStock.classList.remove('hidden');
            }
        }

        // ------------------ ระบบคำนวณและประมวลข้อมูลคลัง (CRUD) ------------------

        function updateOverviewStats() {
            document.getElementById('stat-total-types').innerText = products.length;
            
            let totalQty = 0;
            let totalCost = 0;
            let lowStockCount = 0;

            products.forEach(item => {
                totalQty += parseInt(item.quantity);
                totalCost += (parseInt(item.quantity) * parseFloat(item.cost));
                if (parseInt(item.quantity) <= 5) {
                    lowStockCount++;
                }
            });

            document.getElementById('stat-total-quantity').innerHTML = `${totalQty} <span class="text-xs font-normal">ชิ้น</span>`;
            document.getElementById('stat-total-cost').innerText = `฿${totalCost.toLocaleString()}`;
            document.getElementById('stat-low-stock').innerText = lowStockCount;
        }

        function renderProductTable() {
            const tableBody = document.getElementById('product-table-body');
            const searchVal = document.getElementById('search-input').value.toLowerCase().trim();
            const categoryFilter = document.getElementById('filter-category').value;
            let renderedItemsCount = 0;

            tableBody.innerHTML = '';

            products.forEach(item => {
                // คัดกรองผ่านตัวค้นหาและฟิลเตอร์ประเภท
                const matchSearch = item.name.toLowerCase().includes(searchVal);
                const matchCategory = categoryFilter === 'all' || item.category === categoryFilter;

                if (matchSearch && matchCategory) {
                    renderedItemsCount++;
                    const profit = item.price - item.cost;
                    const expectedTotalProfit = profit * item.quantity;
                    const lowStockAlert = item.quantity <= 5;

                    const row = document.createElement('tr');
                    row.className = "hover:bg-slate-50 dark:hover:bg-slate-900/40 transition-colors";
                    row.innerHTML = `
                        <td class="py-4 px-4 sm:px-6 font-semibold text-slate-900 dark:text-slate-200">${escapeHTML(item.name)}</td>
                        <td class="py-4 px-4">
                            <span class="px-2.5 py-1 bg-slate-100 dark:bg-slate-700 text-slate-600 dark:text-slate-300 rounded-lg text-xs font-semibold">
                                ${item.category}
                            </span>
                        </td>
                        <td class="py-4 px-4 text-center">
                            <span class="px-3 py-1.5 rounded-xl font-bold text-xs ${
                                lowStockAlert 
                                    ? 'bg-rose-100 dark:bg-rose-900/30 text-rose-500 animate-pulse' 
                                    : 'bg-emerald-100 dark:bg-emerald-900/30 text-emerald-600'
                            }">
                                ${item.quantity} ${lowStockAlert ? '<i class="fa-solid fa-triangle-exclamation"></i>' : ''}
                            </span>
                        </td>
                        <td class="py-4 px-4 text-right font-medium text-slate-500">฿${item.cost.toLocaleString()}</td>
                        <td class="py-4 px-4 text-right font-semibold text-slate-800 dark:text-slate-200">฿${item.price.toLocaleString()}</td>
                        <td class="py-4 px-4 text-right text-emerald-600 font-bold">฿${expectedTotalProfit.toLocaleString()}</td>
                        <td class="py-4 px-4">
                            <div class="flex items-center justify-center space-x-2">
                                <button onclick="openEditProductModal(${item.id})" class="p-2 text-indigo-500 hover:bg-indigo-50 dark:hover:bg-indigo-900/30 rounded-lg transition-colors" title="แก้ไขข้อมูล">
                                    <i class="fa-regular fa-pen-to-square"></i>
                                </button>
                                <button onclick="deleteProduct(${item.id})" class="p-2 text-rose-500 hover:bg-rose-50 dark:hover:bg-rose-900/30 rounded-lg transition-colors" title="ลบรายการ">
                                    <i class="fa-regular fa-trash-can"></i>
                                </button>
                            </div>
                        </td>
                    `;
                    tableBody.appendChild(row);
                }
            });

            const emptyElement = document.getElementById('no-products');
            if (renderedItemsCount === 0) {
                emptyElement.classList.remove('hidden');
            } else {
                emptyElement.classList.add('hidden');
            }
        }

        // ตัวกรองสินค้าแบบ Dynamic
        function filterProducts() {
            renderProductTable();
        }

        // ลบสินค้า
        function deleteProduct(id) {
            const productToDelete = products.find(p => p.id === id);
            if (!productToDelete) return;

            // บันทึกประวัติลบสินค้าจำลอง
            addHistoryLog(productToDelete.name, "นำออก (ลบรายการ)", productToDelete.quantity);

            products = products.filter(p => p.id !== id);
            
            updateOverviewStats();
            renderProductTable();
            showToast('ลบสำเร็จ', 'ลบสินค้าชิ้นดังกล่าวออกจากคลังคุมข้อมูลเรียบร้อย', 'info');
        }

        // สั่งเพิ่ม/ปรับสถิติสินค้า
        function openAddProductModal() {
            document.getElementById('product-modal-title').innerText = "เพิ่มสินค้าใหม่เข้าสต็อก";
            document.getElementById('edit-product-id').value = "";
            document.getElementById('product-form').reset();
            document.getElementById('quick-stock-adjust-section').classList.add('hidden');
            
            // เปิดโมดอลแบคดรอป
            document.getElementById('product-modal').classList.remove('hidden');
        }

        function openEditProductModal(id) {
            const product = products.find(p => p.id === id);
            if (!product) return;

            document.getElementById('product-modal-title').innerText = "แก้ไขข้อมูลสินค้าคงคลัง";
            document.getElementById('edit-product-id').value = product.id;
            
            document.getElementById('p-name').value = product.name;
            document.getElementById('p-category').value = product.category;
            document.getElementById('p-qty').value = product.quantity;
            document.getElementById('p-cost').value = product.cost;
            document.getElementById('p-price').value = product.price;

            // แสดงหน้าต่างปรับยอดสต็อกด่วนทันใจ
            document.getElementById('quick-stock-adjust-section').classList.remove('hidden');

            document.getElementById('product-modal').classList.remove('hidden');
        }

        function closeProductModal() {
            document.getElementById('product-modal').classList.add('hidden');
        }

        // ปรับยอดสต็อกด่วนทันควันในขณะเปิดการแก้ไขข้อมูล
        function adjustQuickStock(val) {
            const qtyInput = document.getElementById('p-qty');
            let currentVal = parseInt(qtyInput.value) || 0;
            currentVal = Math.max(0, currentVal + val);
            qtyInput.value = currentVal;
            
            showToast('ปรับข้อมูลจำลอง', 'ทำการเปลี่ยนแปลงตัวเลขสต็อกพร้อมบันทึกประวัติทันที', 'success');
        }

        function handleSaveProduct(event) {
            event.preventDefault();

            const editId = document.getElementById('edit-product-id').value;
            const name = document.getElementById('p-name').value.trim();
            const category = document.getElementById('p-category').value;
            const quantity = parseInt(document.getElementById('p-qty').value) || 0;
            const cost = parseFloat(document.getElementById('p-cost').value) || 0;
            const price = parseFloat(document.getElementById('p-price').value) || 0;

            if (editId) {
                // อัปเดตข้อมูลสินค้าเดิม
                const productIndex = products.findIndex(p => p.id == editId);
                if (productIndex !== -1) {
                    const originalQty = products[productIndex].quantity;
                    const difference = quantity - originalQty;

                    if (difference !== 0) {
                        const actionType = difference > 0 ? "รับเข้า" : "จ่ายออก";
                        addHistoryLog(name, actionType, Math.abs(difference));
                    }

                    products[productIndex] = {
                        ...products[productIndex],
                        name,
                        category,
                        quantity,
                        cost,
                        price
                    };

                    showToast('แก้ไขข้อมูลสำเร็จ', 'อัปเดตข้อมูลสินค้าเข้าคลังฐานสต็อกเรียบร้อยแล้ว', 'success');
                }
            } else {
                // สร้างสินค้าใหม่ในรายการ
                const newProduct = {
                    id: Date.now(),
                    name,
                    category,
                    quantity,
                    cost,
                    price
                };
                products.push(newProduct);
                addHistoryLog(name, "รับเข้า", quantity);
                
                showToast('เพิ่มสินค้าสำเร็จ', 'บันทึกสินค้าใหม่เข้าไปในคลังสินค้าจำลองเรียบร้อย!', 'success');
            }

            closeProductModal();
            updateOverviewStats();
            renderProductTable();
        }

        // ------------------ ระบบควบคุมประวัติบันทึกการทำงาน ------------------
        
        function addHistoryLog(pName, action, quantity) {
            const now = new Date();
            const timestamp = now.toLocaleString('th-TH', { hour12: false });
            
            const log = {
                id: Date.now(),
                pName,
                action,
                quantity,
                timestamp
            };

            stockHistory.unshift(log); // เพิ่มไปบนสุดของอาร์เรย์
            renderHistory();
        }

        function renderHistory() {
            const historyList = document.getElementById('history-list');
            historyList.innerHTML = '';

            if (stockHistory.length === 0) {
                historyList.innerHTML = `
                    <div class="text-center py-16 text-slate-400">
                        <i class="fa-solid fa-receipt text-3xl mb-2"></i>
                        <p class="text-xs">ยังไม่มีความเคลื่อนไหวในสต็อกขณะนี้</p>
                    </div>
                `;
                return;
            }

            stockHistory.forEach(log => {
                const isReceived = log.action === "รับเข้า";
                const isRemoved = log.action.includes("ลบรายการ");
                
                let badgeClass = "bg-emerald-100 dark:bg-emerald-900/30 text-emerald-600";
                if (log.action === "จ่ายออก") {
                    badgeClass = "bg-rose-100 dark:bg-rose-900/30 text-rose-500";
                } else if (isRemoved) {
                    badgeClass = "bg-slate-200 dark:bg-slate-700 text-slate-600 dark:text-slate-300";
                }

                const itemDiv = document.createElement('div');
                itemDiv.className = "flex items-center justify-between p-3 rounded-xl border border-slate-100 dark:border-slate-800 bg-slate-50 dark:bg-slate-900/40 text-xs";
                itemDiv.innerHTML = `
                    <div class="space-y-1 flex-1 min-w-0 pr-2">
                        <p class="font-bold text-slate-800 dark:text-slate-200 truncate">${escapeHTML(log.pName)}</p>
                        <p class="text-[10px] text-slate-400"><i class="fa-regular fa-clock mr-1"></i> ${log.timestamp}</p>
                    </div>
                    <div class="flex items-center space-x-2">
                        <span class="px-2 py-0.5 rounded text-[10px] font-bold ${badgeClass}">${log.action}</span>
                        <span class="font-bold text-sm text-slate-700 dark:text-slate-300">${log.quantity} ชิ้น</span>
                    </div>
                `;
                historyList.appendChild(itemDiv);
            });
        }

        function clearHistory() {
            stockHistory = [];
            renderHistory();
            showToast('ล้างประวัติ', 'ลบประวัติกิจกรรมในคลังสินค้าเรียบร้อยแล้ว', 'info');
        }

        // ------------------ มินิเกมจัดเรียงกล่อง (Mini-game) ------------------

        function playMiniGame() {
            miniGameScore++;
            document.getElementById('game-score').innerText = miniGameScore;

            // เพิ่มเอฟเฟกต์หมุนสั่นสะเทือนกล่องแบบสุ่ม
            const boxIcon = document.getElementById('game-box-icon');
            boxIcon.classList.add('scale-110', 'rotate-12');
            
            setTimeout(() => {
                boxIcon.classList.remove('scale-110', 'rotate-12');
            }, 100);

            if (miniGameScore % 15 === 0) {
                showToast('จัดเรียงรวดเร็วว่องไว! 🎉', `คุณจัดของเรียบร้อยได้ถึง ${miniGameScore} ชิ้น! ยอดเยี่ยมมาก`, 'success');
            }
        }

        // ------------------ การแจ้งเตือน Toast ------------------
        
        let toastTimeout;
        function showToast(title, message, type = 'info') {
            const toast = document.getElementById('toast');
            const toastTitle = document.getElementById('toast-title');
            const toastMessage = document.getElementById('toast-message');
            const iconBox = document.getElementById('toast-icon-box');

            clearTimeout(toastTimeout);

            toastTitle.innerText = title;
            toastMessage.innerText = message;

            if (type === 'success') {
                toast.className = toast.className.replace(/border-[a-z]+-500/g, 'border-emerald-500');
                iconBox.innerHTML = '<i class="fa-solid fa-circle-check text-emerald-500"></i>';
            } else if (type === 'error') {
                toast.className = toast.className.replace(/border-[a-z]+-500/g, 'border-red-500');
                iconBox.innerHTML = '<i class="fa-solid fa-circle-exclamation text-red-500"></i>';
            } else {
                toast.className = toast.className.replace(/border-[a-z]+-500/g, 'border-blue-500');
                iconBox.innerHTML = '<i class="fa-solid fa-circle-info text-blue-500"></i>';
            }

            toast.classList.remove('hidden');
            setTimeout(() => {
                toast.classList.remove('translate-x-full');
            }, 10);

            toastTimeout = setTimeout(() => {
                closeToast();
            }, 4000);
        }

        function closeToast() {
            const toast = document.getElementById('toast');
            toast.classList.add('translate-x-full');
            setTimeout(() => {
                toast.classList.add('hidden');
            }, 300);
        }

        function escapeHTML(str) {
            return str.replace(/[&<>'"]/g, 
                tag => ({
                    '&': '&amp;',
                    '<': '&lt;',
                    '>': '&gt;',
                    "'": '&#39;',
                    '"': '&quot;'
                }[tag] || tag)
            );
        }
    </script>
</body>
</html>
