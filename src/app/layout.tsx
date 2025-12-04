import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";

const geistSans = Geist({
  variable: "--font-geist-sans",
  subsets: ["latin"],
});

const geistMono = Geist_Mono({
  variable: "--font-geist-mono",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  metadataBase: new URL("https://agentic-6e7542d2.vercel.app"),
  title: "Smart Tagger — Unreal Engine Tagging Toolkit",
  description:
    "Download Smart Tagger, an Unreal Engine editor plugin that automates gameplay tagging, metadata stamping, and rename operations for selected actors.",
  openGraph: {
    title: "Smart Tagger — Unreal Engine Tagging Toolkit",
    description:
      "Batch gameplay tags, metadata, and renames from a single editor widget. Download the Unreal Engine plugin and ship organised levels.",
    url: "https://agentic-6e7542d2.vercel.app",
    siteName: "Smart Tagger",
    images: [
      {
        url: "/opengraph-image.svg",
        width: 1200,
        height: 630,
        alt: "Smart Tagger plugin hero banner",
      },
    ],
  },
  twitter: {
    card: "summary_large_image",
    title: "Smart Tagger — Unreal Engine Tagging Toolkit",
    description:
      "Automate gameplay tag clean-up for Unreal Engine with Smart Tagger. Download the plugin and streamline production.",
    images: ["/opengraph-image.svg"],
  },
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <body
        className={`${geistSans.variable} ${geistMono.variable} antialiased`}
      >
        {children}
      </body>
    </html>
  );
}
