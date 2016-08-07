import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
public class Renew implements MouseListener{
	public JFrame frame;
	public JButton yesbt;
	public JButton nobt;
	public JLabel rno;
	public JLabel bno;
	public TextField trno;
	public TextField tbno;
	
	public Connection conn;
	public Statement st;
	public Renew()
	{
		//设置初始界面
		frame=new JFrame();
		frame.setSize(500, 350);
		frame.setTitle("Login/Manage/Renew");
		frame.setLayout(null);
				
		rno=new JLabel();
		bno=new JLabel();
		rno.setText("读者编号：");
		bno.setText("图书编号：");
		rno.setSize(80,30);
		bno.setSize(80,30);
		rno.setLocation(110, 60);
		bno.setLocation(110, 130);
		frame.add(rno);
		frame.add(bno);
				
		trno=new TextField();
		tbno=new TextField();
		trno.setSize(150, 30);
		tbno.setSize(150, 30);
		trno.setLocation(250, 60);
		tbno.setLocation(250, 130);
		frame.add(trno);
		frame.add(tbno);
				
		yesbt=new JButton();
		nobt=new JButton();
		yesbt.setText("续借");
		nobt.setText("还书");
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
	public void mouseClicked(MouseEvent e) {
		JButton source=(JButton)e.getSource();
		String str=source.getText().toString();
		if(str.equals("续借"))
		{	String RNO=trno.getText().toString();
			String BNO=tbno.getText().toString();
			String renew="update BORROW SET RDATE+=3 where RNO="+ RNO+"AND BNO="+BNO;
			try {
				Class.forName("oracle.jdbc.driver.OracleDriver").newInstance();
				String url="jdbc:oracle:thin:@localhost:1521:orcl";
				conn= DriverManager.getConnection(url,"system","admin");
				st=conn.createStatement();
				st.execute(renew);
				conn.close();
				JOptionPane.showMessageDialog(frame,"续借成功");
			}
			catch(Exception e1)
			{
				e1.printStackTrace();
			}
		}
		else
		{
			String RNO=trno.getText().toString();
			String BNO=tbno.getText().toString();
			String retu1="update BORROW SET RDATE=sysdate where RNO="+ RNO+"AND BNO="+BNO;
			String retu2="update BOOK SET CTYPENO=1 where BNO="+ BNO;
			try {
				Class.forName("oracle.jdbc.driver.OracleDriver").newInstance();
				String url="jdbc:oracle:thin:@localhost:1521:orcl";
				conn= DriverManager.getConnection(url,"system","admin");
				st=conn.createStatement();
				st.execute(retu1);
				st.execute(retu2);
				conn.close();
				JOptionPane.showMessageDialog(frame,"还书成功");
			}
			catch(Exception e1)
			{
				e1.printStackTrace();
			}
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
