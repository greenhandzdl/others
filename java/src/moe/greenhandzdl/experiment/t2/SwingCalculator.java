package moe.greenhandzdl.experiment.t2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;


public class SwingCalculator extends JFrame implements ActionListener {

    private JPanel userShowPanel; // 输出显示区域
    private JLabel textOnOutputPanel;

    private JPanel InputNumPanel; // 输入区域
    private JPanel NumPanel,OpPanel;
    private JButton btn0,btn1,btn2,btn3,btn4,btn5,btn6,btn7,btn8,btn9,btndots,btnbackspace
                    ,btnadd,btnsub,btnmul,btndiv,btnequal,btnclear;

    public SwingCalculator() {
        super("Swing Calculator");
        setSize(400, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(null);

        // 初始化显示区域
        userShowPanel = new JPanel();
        userShowPanel.setBounds(50, 20, 300, 50);
        userShowPanel.setBackground(Color.DARK_GRAY);
        userShowPanel.setAlignmentX(Component.RIGHT_ALIGNMENT);
        textOnOutputPanel = new JLabel("欢迎来到我的计算器,请使用清除键清除输入");
        textOnOutputPanel.setFont(new Font("Arial", Font.BOLD, 16));
        textOnOutputPanel.setAlignmentX(Component.RIGHT_ALIGNMENT);
        userShowPanel.add(textOnOutputPanel);
        add(userShowPanel);

        // 初始化输入区域
        InputNumPanel = new JPanel();
        InputNumPanel.setBounds(50, 100, 300, 300);
        InputNumPanel.setLayout(null);

        // 初始化数字按钮面板
        NumPanel = new JPanel();
        NumPanel.setBounds(0, 0, 200, 300);
        NumPanel.setLayout(new GridLayout(4, 3, 5, 5)); // 4行3列，按钮间距为5像素

        // 添加数字按钮到NumPanel
        btn0 = new JButton("0");
        btn1 = new JButton("1");
        btn2 = new JButton("2");
        btn3 = new JButton("3");
        btn4 = new JButton("4");
        btn5 = new JButton("5");
        btn6 = new JButton("6");
        btn7 = new JButton("7");
        btn8 = new JButton("8");
        btn9 = new JButton("9");
        btndots = new JButton(".");
        btnbackspace = new JButton("←");

        NumPanel.add(btn1);
        NumPanel.add(btn2);
        NumPanel.add(btn3);
        NumPanel.add(btn4);
        NumPanel.add(btn5);
        NumPanel.add(btn6);
        NumPanel.add(btn7);
        NumPanel.add(btn8);
        NumPanel.add(btn9);
        NumPanel.add(btndots);
        NumPanel.add(btn0);
        NumPanel.add(btnbackspace);

        // 初始化操作按钮面板
        OpPanel = new JPanel();
        OpPanel.setBounds(210, 0, 90, 300);
        OpPanel.setLayout(new GridLayout(6, 1, 5, 5)); // 5行1列，按钮间距为5像素

        // 添加操作按钮到OpPanel
        btnadd = new JButton("+");
        btnsub = new JButton("-");
        btnmul = new JButton("*");
        btndiv = new JButton("/");
        btnequal = new JButton("=");
        btnclear = new JButton("CLS");

        OpPanel.add(btnadd);
        OpPanel.add(btnsub);
        OpPanel.add(btnmul);
        OpPanel.add(btndiv);
        OpPanel.add(btnequal);
        OpPanel.add(btnclear);

        // 将NumPanel和OpPanel添加到InputNumPanel
        InputNumPanel.add(NumPanel);
        InputNumPanel.add(OpPanel);

        // 将InputNumPanel添加到Calculator
        add(InputNumPanel);

        // 显示窗口
        setVisible(true);
    }

    public void listenToBtn() {
        // 为数字按钮设置监听器和ActionCommand
        btn0.setActionCommand("0");
        btn1.setActionCommand("1");
        btn2.setActionCommand("2");
        btn3.setActionCommand("3");
        btn4.setActionCommand("4");
        btn5.setActionCommand("5");
        btn6.setActionCommand("6");
        btn7.setActionCommand("7");
        btn8.setActionCommand("8");
        btn9.setActionCommand("9");
        btndots.setActionCommand(".");
        btnbackspace.setActionCommand("BACKSPACE");

        btn0.addActionListener(this);
        btn1.addActionListener(this);
        btn2.addActionListener(this);
        btn3.addActionListener(this);
        btn4.addActionListener(this);
        btn5.addActionListener(this);
        btn6.addActionListener(this);
        btn7.addActionListener(this);
        btn8.addActionListener(this);
        btn9.addActionListener(this);
        btndots.addActionListener(this);
        btnbackspace.addActionListener(this);

        // 为操作按钮设置监听器和ActionCommand
        btnadd.setActionCommand("+");
        btnsub.setActionCommand("-");
        btnmul.setActionCommand("*");
        btndiv.setActionCommand("/");
        btnequal.setActionCommand("=");
        btnclear.setActionCommand("CLEAR");

        btnadd.addActionListener(this);
        btnsub.addActionListener(this);
        btnmul.addActionListener(this);
        btndiv.addActionListener(this);
        btnequal.addActionListener(this);
        btnclear.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();

        switch (command) {
            case "0": case "1": case "2": case "3": case "4":
            case "5": case "6": case "7": case "8": case "9":
            case ".":
                // 数字和小数点按钮
                textOnOutputPanel.setText(textOnOutputPanel.getText() + command);
                break;

            case "BACKSPACE":
                // 回退按钮
                String currentText = textOnOutputPanel.getText();
                if (!currentText.isEmpty()) {
                    textOnOutputPanel.setText(currentText.substring(0, currentText.length() - 1));
                }
                break;

            case "+": case "-": case "*": case "/":
                // 操作符按钮
                textOnOutputPanel.setText(textOnOutputPanel.getText() + command);
                break;

            case "CLEAR":
                // 清除按钮
                textOnOutputPanel.setText("");
                break;

            case "=":
                // 等号按钮
                try {
                    double result = evaluateExpression(textOnOutputPanel.getText());
                    textOnOutputPanel.setText(String.valueOf(result));
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(
                            this,
                            "输入错误：" + ex.getMessage(),
                            "错误",
                            JOptionPane.ERROR_MESSAGE
                    );
                }
                break;

            default:
                throw new IllegalArgumentException("未知命令：" + command);
        }
    }

    public double evaluateExpression(String expression) throws Exception {
        // 检查表达式是否合法
        if (!expression.matches("^[0-9+\\-*/().\\s]+$")) {
            throw new IllegalArgumentException("表达式包含非法字符！");
        }

        // 去掉空格
        expression = expression.replaceAll("\\s+", "");

        // 转换为后缀表达式
        List<String> postfix = infixToPostfix(expression);

        // 计算后缀表达式的值
        return evaluatePostfix(postfix);
    }

    private List<String> infixToPostfix(String expression) throws Exception {
        List<String> postfix = new ArrayList<>();
        Stack<Character> operators = new Stack<>();
        int length = expression.length();

        for (int i = 0; i < length; i++) {
            char c = expression.charAt(i);

            // 如果是数字或小数点，读取完整的数字
            if (Character.isDigit(c) || c == '.') {
                StringBuilder number = new StringBuilder();
                while (i < length && (Character.isDigit(expression.charAt(i)) || expression.charAt(i) == '.')) {
                    number.append(expression.charAt(i));
                    i++;
                }
                i--; // 回退一位
                postfix.add(number.toString());
            }
            // 如果是左括号
            else if (c == '(') {
                operators.push(c);
            }
            // 如果是右括号
            else if (c == ')') {
                while (!operators.isEmpty() && operators.peek() != '(') {
                    postfix.add(String.valueOf(operators.pop()));
                }
                if (operators.isEmpty() || operators.pop() != '(') {
                    throw new Exception("括号不匹配！");
                }
            }
            // 如果是操作符
            else if (isOperator(c)) {
                while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(c)) {
                    postfix.add(String.valueOf(operators.pop()));
                }
                operators.push(c);
            } else {
                throw new IllegalArgumentException("非法字符：" + c);
            }
        }

        // 弹出栈中剩余的操作符
        while (!operators.isEmpty()) {
            char op = operators.pop();
            if (op == '(' || op == ')') {
                throw new Exception("括号不匹配！");
            }
            postfix.add(String.valueOf(op));
        }

        return postfix;
    }

    private double evaluatePostfix(List<String> postfix) throws Exception {
        Stack<Double> stack = new Stack<>();

        for (String token : postfix) {
            // 如果是数字
            if (isNumeric(token)) {
                stack.push(Double.parseDouble(token));
            }
            // 如果是操作符
            else if (isOperator(token.charAt(0))) {
                if (stack.size() < 2) {
                    throw new Exception("表达式错误！");
                }
                double b = stack.pop();
                double a = stack.pop();
                switch (token.charAt(0)) {
                    case '+':
                        stack.push(a + b);
                        break;
                    case '-':
                        stack.push(a - b);
                        break;
                    case '*':
                        stack.push(a * b);
                        break;
                    case '/':
                        if (b == 0) {
                            throw new ArithmeticException("除数不能为零！");
                        }
                        stack.push(a / b);
                        break;
                    default:
                        throw new IllegalArgumentException("未知操作符：" + token);
                }
            } else {
                throw new IllegalArgumentException("非法后缀表达式元素：" + token);
            }
        }

        if (stack.size() != 1) {
            throw new Exception("表达式错误！");
        }

        return stack.pop();
    }

    private boolean isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    private int precedence(char operator) {
        switch (operator) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            default:
                return -1;
        }
    }

    private boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static void main(String[] args) {
        SwingCalculator calculator = new SwingCalculator();
        calculator.listenToBtn();
    }

}