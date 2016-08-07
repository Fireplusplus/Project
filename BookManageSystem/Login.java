import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;

public class Login implements MouseListener
{
	
	public JFrame frame;
	public JButton yesbt;
	public JButton nobt;
	public JLabel userlb;
	public JLabel pswlb;
	public TextField usertxt;
	public JPasswordField pswtxt;
	
	public Connection conn;
	public Statement st;
	
	public Login()
	{	//设置初始界面
		frame=new JFrame();
		frame.setSize(500, 350);
		frame.setTitle("Login");
		frame.setLayout(null);
		
		userlb=new JLabel();
		pswlb=new JLabel();
		userlb.setText("用户名：");
		pswlb.setText("密    码：");
		userlb.setSize(80,30);
		pswlb.setSize(80,30);
		userlb.setLocation(110, 60);
		pswlb.setLocation(110, 130);
		frame.add(userlb);
		frame.add(pswlb);
		
		usertxt=new TextField();
		pswtxt=new JPasswordField();
		usertxt.setSize(150, 30);
		pswtxt.setSize(150, 30);
		usertxt.setLocation(250, 60);
		pswtxt.setLocation(250, 130);
		frame.add(usertxt);
		frame.add(pswtxt);
		
		yesbt=new JButton();
		nobt=new JButton();
		yesbt.setText("登录");
		nobt.setText("退出");
		yesbt.setSize(80,35);
		nobt.setSize(80,35);
		yesbt.setLocation(100, 235);
		nobt.setLocation(300, 235);
		frame.add(yesbt);
		frame.add(nobt);
		
		nobt.addMouseListener(this);
		yesbt.addMouseListener(this);
		
		frame.setVisible(true);
	}

	@Override
	public void mouseClicked(MouseEvent e) 
	{	JButton source=(JButton)e.getSource();
		if(source.getText().toString().equals("登录"))
		{	
			try {
			Class.forName("oracle.jdbc.driver.OracleDriver").newInstance();
			//注册并加载驱动
			String url="jdbc:oracle:thin:@localhost:1521:orcl";
			//配置连接字符串
			conn= DriverManager.getConnection(url,"system","admin");
			//创建数据库连接对象
			st=conn.createStatement();
			//数据库执行对象
			String username=usertxt.getText().toString();
			String psw=pswtxt.getText().toString();
			String login="SELECT KEY FROM ADMIN WHERE ACCOUNT='skd'";
			ResultSet rs=st.executeQuery(login);
			
			if(rs.next() && rs.getString(1).equals(psw))
			{
				frame.setVisible(false);
				//进入功能选择页面
				Manage manage=new Manage();
			}
			else
				System.out.println("用户名或密码错误");
			conn.close();
			}
			catch(SQLException ex){
				JOptionPane.showMessageDialog(frame,ex);
			}
			catch (Exception ex){
				JOptionPane.showMessageDialog(frame,ex);
			} 
		}
		else
		{	
			System.exit(0);
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

}